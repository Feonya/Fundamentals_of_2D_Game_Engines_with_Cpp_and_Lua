#include <iostream>
#include "constants.h"
#include "Game.h"

int main(int argc, char* argv[])
{
  Game* game = new Game();

  game->Initialize(k_windowWidth, k_windowHeight);

  while (game->IsRunning())
  {
    game->HandleInput();
    game->Update();
    game->Render();
  }

  game->Destroy();

  return 0;
}
