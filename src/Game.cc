#include <iostream>
#include "glm/glm.hpp"
#include "constants.h"
#include "AssetManager.h"
#include "components/TransformComponent.h"
#include "components/SpriteComponent.h"
#include "components/KeyboardControlComponent.h"
#include "Map.h"
#include "Game.h"

EntityManager g_manager;
AssetManager* Game::assetManager = new AssetManager(&g_manager);
SDL_Renderer* Game::renderer;
SDL_Event     Game::event;
Map*          g_map;

Game::Game() { isRunning = false; }

Game::~Game() {}

bool Game::IsRunning() const
{
  return isRunning;
}

void Game::Initialize(int f_width, int f_height)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    std::cerr << "Error initializing SDL." << std::endl;
    return;
  }

  window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, f_width,
      f_height, SDL_WINDOW_BORDERLESS);
  if (!window)
  {
    std::cerr << "Error creating SDL window." << std::endl;
    return;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer)
  {
    std::cerr << "Error creating SDL renderer." << std::endl;
    return;
  }

  LoadLevel(0);

  isRunning = true;
  return;
}

void Game::LoadLevel(int f_levelNumber)
{
  /* Start including new assets to the assetManager list. */
  assetManager->AddTexture("tank-image",
      std::string("assets/images/tank-big-right.png").c_str());
  assetManager->AddTexture("chopper-image",
      std::string("assets/images/chopper-spritesheet.png").c_str());
  assetManager->AddTexture("radar-image", std::string("assets/images/radar.png").c_str());
  assetManager->AddTexture("jungle-tiletexture",
      std::string("assets/tilemaps/jungle.png").c_str());

  g_map = new Map("jungle-tiletexture", 1, 32);
  g_map->LoadMap("assets/tilemaps/jungle.map", 25, 20);

  /* Start including entities and also components to them. */
  Entity& l_tankEntity(g_manager.AddEntity("tank"));
  l_tankEntity.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
  l_tankEntity.AddComponent<SpriteComponent>("tank-image");

  Entity& l_chopperEntity(g_manager.AddEntity("chopper"));
  l_chopperEntity.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
  l_chopperEntity.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
  l_chopperEntity.AddComponent<KeyboardControlComponent>("up", "right", "down", "left", "shoot");

  Entity& l_radarEntity(g_manager.AddEntity("radar"));
  l_radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
  l_radarEntity.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);
}

void Game::HandleInput()
{
  SDL_PollEvent(&event);

  switch (event.type)
  {
    case SDL_QUIT:
      isRunning = false;
      break;

    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE)
        isRunning = false;
      break;

    default:
      break;
  }
}

void Game::Update()
{
  // Wait until 16ms has elapsed since the last frame.
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + k_frameTargetTime));

  // Delta time is the difference in ticks from last frame converted to seconds.
  float l_deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.f;
  // Clamp deltaTime to a maximum value.
  l_deltaTime = l_deltaTime > .05f ? .05f : l_deltaTime;

  // Sets the new ticks form the current frame to be used in the next pass.
  ticksLastFrame = SDL_GetTicks();

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
  SDL_DestroyWindow(window);
  SDL_Quit();
}
