#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <SDL2/SDL.h>
#include "glm/glm.hpp"
#include "../EntityManager.h"
#include "../Game.h"

class TransformComponent : public Component {
  public:
    glm::vec2 position;
    glm::vec2 velocity;
    int width;
    int height;
    int scale;

    TransformComponent(int f_posX, int f_posY, int f_velX, int f_velY, int f_w, int f_h, int f_s)
    {
      position = glm::vec2(f_posX, f_posY);
      velocity = glm::vec2(f_velX, f_velY);
      width    = f_w;
      height   = f_h;
      scale    = f_s;
    }

    void Initialize() override {}

    void Update(float f_deltaTime) override
    {
      position.x += velocity.x * f_deltaTime;
      position.y += velocity.y * f_deltaTime;
    }

    void Render() override {}

};

#endif
