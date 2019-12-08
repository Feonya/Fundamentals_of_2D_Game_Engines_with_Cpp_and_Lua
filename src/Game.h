#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Entity.h"
#include "EntityManager.h"
#include "Component.h"

class Game {
  public:
    static SDL_Renderer* Renderer;
    Game();
    ~Game();
    bool IsRunning() const;
    void Initialize(int width, int height);
    void LoadLevel(int levelNumber);
    void HandleInput();
    void Update();
    void Render();
    void Destroy();

  private:
    SDL_Window* window_;
    bool is_running_;
    int ticks_last_frame_;
};

#endif
