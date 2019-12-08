#include <iostream>
#include "glm/glm.hpp"
#include "constants.h"
#include "Game.h"

// EntityManager gManager;
SDL_Renderer* Game::Renderer;

Game::Game() : is_running_(false) {}

Game::~Game() {}

bool Game::IsRunning() const
{
  return is_running_;
}

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

  Renderer = SDL_CreateRenderer(window_, -1, 0);
  if (!Renderer)
  {
    std::cerr << "Error creating SDL renderer." << std::endl;
    return;
  }

  is_running_ = true;
  return;
}

void Game::LoadLevel(int levelNumber)
{
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
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticks_last_frame_ + kFrameTargetTime));

  // Delta time is the difference in ticks from last frame converted to seconds.
  float deltaTime = (SDL_GetTicks() - ticks_last_frame_) / 1000.f;
  // Clamp deltaTime to a maximum value.
  deltaTime = deltaTime > .05f ? .05f : deltaTime;

  // Sets the new ticks form the current frame to be used in the next pass.
  ticks_last_frame_ = SDL_GetTicks();

  // TODO:
  // Here we call the manager update to update all entities as function of delta time.
}

void Game::Render()
{
  SDL_SetRenderDrawColor(Renderer, 21, 21, 21, 255);
  SDL_RenderClear(Renderer);

  // TODO:
  // Here we call the manager render to render all entities.

  SDL_RenderPresent(Renderer);
}

void Game::Destroy()
{
  SDL_DestroyRenderer(Renderer);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}
