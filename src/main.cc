#include <iostream>
#include "constants.h"
#include "Game.h"

int main(int argc, char* argv[])
{
  Game* l_game = new Game();

  l_game->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

  while (l_game->IsRunning())
  {
    l_game->HandleInput();
    l_game->Update();
    l_game->Render();
  }

  l_game->Destroy();

  return 0;
}
