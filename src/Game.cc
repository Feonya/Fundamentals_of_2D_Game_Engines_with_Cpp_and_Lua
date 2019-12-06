#include <iostream>
#include "constants.h"
#include "Game.h"

Game::Game() : is_running_(false) {}

Game::~Game() {}

bool Game::IsRunning() const
{
  return is_running_;
}

float ProjectilePosX = 0.0f;
float ProjectilePosY = 0.0f;
// Vel means Velocity.
float ProjectileVelX = 0.05f;
float ProjectileVelY = 0.05f;

void Game::Initialize(int width, int height)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    std::cerr << "Error initializing SDL." << std::endl;
    return;
  }

  window_ = SDL_CreateWindow(
    NULL,
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    width, height,
    SDL_WINDOW_BORDERLESS
  );
  if (!window_)
  {
    std::cerr << "Error creating SDL window." << std::endl;
    return;
  }

  renderer_ = SDL_CreateRenderer(window_, -1, 0);
  if (!renderer_)                           
  {
    std::cerr << "Error creating SDL renderer." << std::endl;
    return;
  }

  is_running_ = true;
  return;
}

void Game::HandleInput()
{
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type)
  {
    case SDL_QUIT:
      is_running_ = false;
      break;

    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE)
        is_running_ = false;
      break;

    default:
      break;
  }
}

void Game::Update()
{
  ProjectilePosX += ProjectileVelX;
  ProjectilePosY += ProjectileVelY;
}

void Game::Render()
{
  SDL_SetRenderDrawColor(renderer_, 21, 21, 21, 255);
  SDL_RenderClear(renderer_);

  SDL_Rect projectile {
    (int)ProjectilePosX, (int)ProjectilePosY,
    10, 10
  };

  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer_, &projectile);

  SDL_RenderPresent(renderer_);
}

void Game::Destroy()
{
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}
