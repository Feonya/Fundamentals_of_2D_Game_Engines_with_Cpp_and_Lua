#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Game {
  public:
    Game();
    ~Game();
    bool IsRunning() const;
    void Initialize(int width, int height);
    void HandleInput();
    void Update();
    void Render();
    void Destroy();

  private:
    SDL_Window*   window_;
    SDL_Renderer* renderer_;
    bool          is_running_;
};

#endif
