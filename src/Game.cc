#include <iostream>
#include "glm/glm.hpp"
#include "constants.h"
#include "Game.h"
#include "AssetManager.h"
#include "components/TransformComponent.h"
#include "components/SpriteComponent.h"

EntityManager g_manager;
AssetManager* Game::m_assetManager = new AssetManager(&g_manager);
SDL_Renderer* Game::m_renderer;

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

  m_renderer = SDL_CreateRenderer(m_window, -1, 0);
  if (!m_renderer)
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
  m_assetManager->AddTexture("tank-image",
      std::string("assets/images/tank-big-right.png").c_str());
  m_assetManager->AddTexture("chopper-image",
      std::string("assets/images/chopper-spritesheet.png").c_str());
  m_assetManager->AddTexture("radar-image",
      std::string("assets/images/radar.png").c_str());

  // Start including entities and also components to them.
  Entity& tankEntity(g_manager.AddEntity("tank"));
  tankEntity.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
  tankEntity.AddComponent<SpriteComponent>("tank-image");

  Entity& chopperEntity(g_manager.AddEntity("chopper"));
  chopperEntity.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
  chopperEntity.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);

  Entity& radarEntity(g_manager.AddEntity("Radar"));
  radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
  radarEntity.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);
}

void Game::HandleInput()
{
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type)
  {
    case SDL_QUIT:
      m_isRunning = false;
      break;

    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE)
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
  float deltaTime = (SDL_GetTicks() - m_ticksLastFrame) / 1000.f;
  // Clamp deltaTime to a maximum value.
  deltaTime = deltaTime > .05f ? .05f : deltaTime;

  // Sets the new ticks form the current frame to be used in the next pass.
  m_ticksLastFrame = SDL_GetTicks();

  g_manager.Update(deltaTime);
}

void Game::Render()
{
  SDL_SetRenderDrawColor(m_renderer, 21, 21, 21, 255);
  SDL_RenderClear(m_renderer);

  if (g_manager.HasNoEntities()) return;
  g_manager.Render();

  SDL_RenderPresent(m_renderer);
}

void Game::Destroy()
{
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}
