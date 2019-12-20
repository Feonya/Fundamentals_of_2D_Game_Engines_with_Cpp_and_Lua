#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <lua5.3/lua.hpp>
#include "Entity.h"
#include "EntityManager.h"
#include "Component.h"

class AssetManager;

class Game {
  public:
    static SDL_Renderer* renderer;
    static AssetManager* assetManager;
    static SDL_Event     event;
    static SDL_Rect      camera;

    Game();
    ~Game();

    bool IsRunning() const;
    void Initialize(int f_width, int f_height);
    void LoadLevel(int f_levelNumber);
    void HandleInput();
    void Update();
    void Render();
    void Destroy();
    void HandleCameraMovement();
    void CheckCollisions();
    void ProcessGameOver();
    void ProcessNextLevel();

  private:
    SDL_Window* window;
    bool isRunning;
    int  ticksLastFrame;
};

#endif
