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
Entity*       g_player = NULL;

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

  LoadLevel(1);

  isRunning = true;
  return;
}

void Game::LoadLevel(int f_levelNumber)
{
  lua_State* l_lua = luaL_newstate();

  luaopen_base(l_lua);
  luaopen_os(l_lua);
  luaopen_math(l_lua);

  std::string l_levelName = "level" + std::to_string(f_levelNumber);
  int l_rst = luaL_dofile(l_lua, ("assets/scripts/" + l_levelName + ".lua").c_str());
  if (l_rst == LUA_OK)
  {
    lua_getglobal(l_lua, l_levelName.c_str());

    /**************************************/
    /* Loads Assets From Lua Config File. */
    /**************************************/
    lua_pushstring(l_lua, "assets");
    lua_gettable(l_lua, -2);

    lua_pushnil(l_lua);
    while (lua_next(l_lua, -2) != 0)
    {
      lua_pushstring(l_lua, "type");
      lua_gettable(l_lua, -2);
      std::string l_assetType = std::string(lua_tostring(l_lua, -1));
      lua_pop(l_lua, 1);

      if (l_assetType.compare("texture") == 0)
      {
        lua_pushstring(l_lua, "id");
        lua_gettable(l_lua, -2);
        std::string l_assetId = lua_tostring(l_lua, -1);
        lua_pop(l_lua, 1);

        lua_pushstring(l_lua, "file");
        lua_gettable(l_lua, -2);
        std::string l_assetFile = lua_tostring(l_lua, -1);
        lua_pop(l_lua, 1);

        assetManager->AddTexture(l_assetId, l_assetFile.c_str());
      }
      else if (l_assetType.compare("font") == 0)
      {
        lua_pushstring(l_lua, "id");
        lua_gettable(l_lua, -2);
        std::string l_assetId = lua_tostring(l_lua, -1);
        lua_pop(l_lua, 1);

        lua_pushstring(l_lua, "file");
        lua_gettable(l_lua, -2);
        std::string l_assetFile = lua_tostring(l_lua, -1);
        lua_pop(l_lua, 1);

        lua_pushstring(l_lua, "fontSize");
        lua_gettable(l_lua, -2);
        int l_assetFontSize = lua_tonumber(l_lua, -1);
        lua_pop(l_lua, 1);

        assetManager->AddFont(l_assetId, l_assetFile.c_str(), l_assetFontSize);
      }

      lua_pop(l_lua, 1);
    }

    lua_settop(l_lua, 0);
    lua_getglobal(l_lua, l_levelName.c_str());

    /***********************************/
    /* Loads Map From Lua Config File. */
    /***********************************/
    lua_pushstring(l_lua, "map");
    lua_gettable(l_lua, -2);

    lua_pushstring(l_lua, "textureAssetId");
    lua_gettable(l_lua, -2);
    std::string l_mapTextureId = lua_tostring(l_lua, -1);
    lua_pop(l_lua, 1);

    lua_pushstring(l_lua, "file");
    lua_gettable(l_lua, -2);
    std::string l_mapFile = lua_tostring(l_lua, -1);
    lua_pop(l_lua, 1);

    lua_pushstring(l_lua, "scale");
    lua_gettable(l_lua, -2);
    int l_mapScale = lua_tonumber(l_lua, -1);
    lua_pop(l_lua, 1);

    lua_pushstring(l_lua, "tileSize");
    lua_gettable(l_lua, -2);
    int l_mapTileSize = lua_tonumber(l_lua, -1);
    lua_pop(l_lua, 1);

    lua_pushstring(l_lua, "mapSizeX");
    lua_gettable(l_lua, -2);
    int l_mapSizeX = lua_tonumber(l_lua, -1);
    lua_pop(l_lua, 1);

    lua_pushstring(l_lua, "mapSizeY");
    lua_gettable(l_lua, -2);
    int l_mapSizeY = lua_tonumber(l_lua, -1);
    lua_pop(l_lua, 1);

    g_map = new Map {l_mapTextureId , l_mapScale, l_mapTileSize};
    g_map->LoadMap(l_mapFile, l_mapSizeX, l_mapSizeY);
  }
  else
    std::cout << "Error doing Lua file." << std::endl;

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
  if (g_player)
  {
    TransformComponent* l_mainPlayerTransform = g_player->GetComponent<TransformComponent>();

    camera.x = l_mainPlayerTransform->position.x - (WINDOW_WIDTH  / 2);
    camera.y = l_mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

    camera.x = camera.x < 0 ? 0 : camera.x;
    camera.y = camera.y < 0 ? 0 : camera.y;
    camera.x = camera.x > camera.w ? camera.w : camera.x;
    camera.y = camera.y > camera.h ? camera.h : camera.y;
  }
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
