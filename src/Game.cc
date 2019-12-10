#include <iostream>
#include "glm/glm.hpp"
#include "constants.h"
#include "Game.h"
#include "AssetManager.h"
#include "components/TransformComponent.h"
#include "components/SpriteComponent.h"

EntityManager g_manager;
AssetManager* Game::assetManager = new AssetManager(&g_manager);
SDL_Renderer* Game::renderer;

Game::Game() : m_isRunning(false) {}

Game::~Game() {}

bool Game::IsRunning() const
{
  return m_isRunning;
}

void Game::Initialize(int f_width, int f_height)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    std::cerr << "Error initializing SDL." << std::endl;
    return;
  }

  m_window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, f_width,
      f_height, SDL_WINDOW_BORDERLESS);
  if (!m_window)
  {
    std::cerr << "Error creating SDL window." << std::endl;
    return;
  }

  renderer = SDL_CreateRenderer(m_window, -1, 0);
  if (!renderer)
  {
    std::cerr << "Error creating SDL renderer." << std::endl;
    return;
  }

  LoadLevel(0);

  m_isRunning = true;
  return;
}

void Game::LoadLevel(int f_levelNumber)
{
  // Start including new assets to the assetManager list.

  std::string l_textureFilePath = "assets/images/tank-big-right.png";
  assetManager->AddTexture("tank-image", l_textureFilePath.c_str());

  // Start including entities and also components to them.

  Entity& l_newEntity(g_manager.AddEntity("tank"));
  l_newEntity.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
  l_newEntity.AddComponent<SpriteComponent>("tank-image");
}

void Game::HandleInput()
{
  SDL_Event l_event;
  SDL_PollEvent(&l_event);

  switch (l_event.type)
  {
    case SDL_QUIT:
      m_isRunning = false;
      break;

    case SDL_KEYDOWN:
      if (l_event.key.keysym.sym == SDLK_ESCAPE)
        m_isRunning = false;
      break;

    default:
      break;
  }
}

void Game::Update()
{
  // Wait until 16ms has elapsed since the last frame.
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticksLastFrame + k_frameTargetTime));

  // Delta time is the difference in ticks from last frame converted to seconds.
  float l_deltaTime = (SDL_GetTicks() - m_ticksLastFrame) / 1000.f;
  // Clamp deltaTime to a maximum value.
  l_deltaTime = l_deltaTime > .05f ? .05f : l_deltaTime;

  // Sets the new ticks form the current frame to be used in the next pass.
  m_ticksLastFrame = SDL_GetTicks();

  g_manager.Update(l_deltaTime);
}

void Game::Render()
{
  SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
  SDL_RenderClear(renderer);

  if (g_manager.HasNoEntities()) return;
  g_manager.Render();

  SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}
