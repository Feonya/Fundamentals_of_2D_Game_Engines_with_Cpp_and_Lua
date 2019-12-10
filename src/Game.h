#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Entity.h"
#include "EntityManager.h"
#include "Component.h"

class AssetManager;

class Game {
  public:
    static SDL_Renderer* m_renderer;
    static AssetManager* m_assetManager;

    Game();
    ~Game();

    bool IsRunning() const;
    void Initialize(int f_width, int f_height);
    void LoadLevel(int f_levelNumber);
    void HandleInput();
    void Update();
    void Render();
    void Destroy();

  private:
    SDL_Window* m_window;
    bool m_isRunning;
    int m_ticksLastFrame;
};

#endif
