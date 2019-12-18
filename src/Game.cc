#include <iostream>
#include "glm/glm.hpp"
#include "AssetManager.h"
#include "components/TransformComponent.h"
#include "components/SpriteComponent.h"
#include "components/KeyboardControlComponent.h"
#include "components/ColliderComponent.h"
#include "components/TextLabelComponent.h"
#include "components/ProjectileEmitterComponent.h"
#include "Map.h"
#include "Game.h"

EntityManager g_manager;
AssetManager* Game::assetManager = new AssetManager(&g_manager);
SDL_Renderer* Game::renderer;
SDL_Event     Game::event;
SDL_Rect      Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
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

  if (TTF_Init() != 0)
  {
    std::cerr << "Error initializing SDL TTF." << std::endl;
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

Entity& g_player(g_manager.AddEntity("chopper", PLAYER_LAYER));

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
  assetManager->AddTexture("collider-image",
      std::string("assets/images/collision-texture.png").c_str());
  assetManager->AddTexture("heliport-image", std::string("assets/images/heliport.png").c_str());
  assetManager->AddTexture("projectile-image",
      std::string("assets/images/bullet-enemy.png").c_str());

  assetManager->AddFont("charriot-font", std::string("assets/fonts/charriot.ttf").c_str(), 14);

  g_map = new Map("jungle-tiletexture", 2, 32);
  g_map->LoadMap("assets/tilemaps/jungle.map", 25, 20);

  /* Start including entities and also components to them. */
  g_player.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
  g_player.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
  g_player.AddComponent<KeyboardControlComponent>("up", "right", "down", "left", "shoot");
  g_player.AddComponent<ColliderComponent>("player", 240, 106, 32, 32, true);

  Entity& l_tankEntity(g_manager.AddEntity("tank", ENEMY_LAYER));
  l_tankEntity.AddComponent<TransformComponent>(150, 495, 0, 0, 32, 32, 1);
  l_tankEntity.AddComponent<SpriteComponent>("tank-image");
  l_tankEntity.AddComponent<ColliderComponent>("enemy", 150, 495, 32, 32, true);

  Entity& l_projectileEntity(g_manager.AddEntity("projectile", PROJECTILE_LAYER));
  l_projectileEntity.AddComponent<TransformComponent>(150+16, 495+16, 0, 0, 4, 4, 1);
  l_projectileEntity.AddComponent<SpriteComponent>("projectile-image");
  l_projectileEntity.AddComponent<ColliderComponent>("projectile", 150+16, 495+16, 4, 4, false);
  l_projectileEntity.AddComponent<ProjectileEmitterComponent>(50, 270, 200, true);

  Entity& l_radarEntity(g_manager.AddEntity("radar", UI_LAYER));
  l_radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
  l_radarEntity.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);

  Entity& l_heliportEntity(g_manager.AddEntity("heliport", OBSTACLE_LAYER));
  l_heliportEntity.AddComponent<TransformComponent>(470, 420, 0, 0, 32, 32, 1);
  l_heliportEntity.AddComponent<SpriteComponent>("heliport-image");
  l_heliportEntity.AddComponent<ColliderComponent>("level_complete", 470, 420, 32, 32, false);

  Entity& l_labelLevelNameEntity(g_manager.AddEntity("label_level_name", UI_LAYER));
  l_labelLevelNameEntity.AddComponent<TextLabelComponent>(10, 10, "First Level...",
      "charriot-font", WHITE_COLOR);
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
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));

  // Delta time is the difference in ticks from last frame converted to seconds.
  float l_deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.f;
  // Clamp deltaTime to a maximum value.
  l_deltaTime = l_deltaTime > .05f ? .05f : l_deltaTime;

  // Sets the new ticks form the current frame to be used in the next pass.
  ticksLastFrame = SDL_GetTicks();

  g_manager.Update(l_deltaTime);

  HandleCameraMovement();

  CheckCollisions();
}

void Game::Render()
{
  SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
  SDL_RenderClear(renderer);

  if (g_manager.HasNoEntities()) return;
  g_manager.Render();

  SDL_RenderPresent(renderer);
}

void Game:: HandleCameraMovement()
{
  TransformComponent* l_mainPlayerTransform = g_player.GetComponent<TransformComponent>();

  camera.x = l_mainPlayerTransform->position.x - (WINDOW_WIDTH  / 2);
  camera.y = l_mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

  camera.x = camera.x < 0 ? 0 : camera.x;
  camera.y = camera.y < 0 ? 0 : camera.y;
  camera.x = camera.x > camera.w ? camera.w : camera.x;
  camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Game::CheckCollisions()
{
  CollisionType collisionType = g_manager.CheckCollisions();
  if (collisionType == PLAYER_PROJECTILE_COLLISION)     ProcessGameOver();
  if (collisionType == PLAYER_LEVEL_COMPLETE_COLLISION) ProcessNextLevel();
}

void Game::ProcessGameOver()
{
  std::cout << "Game Over" << std::endl;
  isRunning = false;
}

void Game::ProcessNextLevel()
{
  std::cout << "Next Level" << std::endl;
  isRunning = false;
}

void Game::Destroy()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
