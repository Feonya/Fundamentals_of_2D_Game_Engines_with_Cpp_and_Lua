#include <iostream>
#include "glm/glm.hpp"
#include "constants.h"
#include "Game.h"

Game::Game() : is_running_(false) {}

Game::~Game() {}

bool Game::IsRunning() const
{
  return is_running_;
}

glm::vec2 ProjectilePos = glm::vec2(0.f, 0.f);
glm::vec2 ProjectileVel = glm::vec2(20.f, 10.f);

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
  // Wait until 16ms has elapsed since the last frame.
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticks_last_frame_ + FRAME_TARGET_TIME));

  // Delta time is the difference in ticks from last frame converted to seconds.
  float deltaTime = (SDL_GetTicks() - ticks_last_frame_) / 1000.f;
  // Clamp deltaTime to a maximum value.
  deltaTime = deltaTime > .05f ? .05f : deltaTime;

  // Sets the new ticks form the current frame to be used in the next pass.
  ticks_last_frame_ = SDL_GetTicks();

  // Use deltaTime to update my game objects.
  ProjectilePos = glm::vec2(
    ProjectilePos.x + ProjectileVel.x * deltaTime,
    ProjectilePos.y + ProjectileVel.y * deltaTime
  );
}

void Game::Render()
{
  SDL_SetRenderDrawColor(renderer_, 21, 21, 21, 255);
  SDL_RenderClear(renderer_);

  SDL_Rect projectile {
    (int)ProjectilePos.x, (int)ProjectilePos.y,
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
