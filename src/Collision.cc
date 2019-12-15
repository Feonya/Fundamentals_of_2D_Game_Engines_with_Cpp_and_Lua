#include "Collision.h"

bool Collision::CheckRectangleCollision(const SDL_Rect& f_rectangleA,
    const SDL_Rect& f_rectangleB)
{
  return f_rectangleA.x + f_rectangleA.w >= f_rectangleB.x &&
         f_rectangleB.x + f_rectangleB.w >= f_rectangleA.x &&
         f_rectangleA.y + f_rectangleA.h >= f_rectangleB.y &&
         f_rectangleB.y + f_rectangleB.h >= f_rectangleA.y;
}
