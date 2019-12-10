#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <SDL2/SDL.h>
#include "glm/glm.hpp"
#include "../EntityManager.h"
#include "../Game.h"

class TransformComponent : public Component {
  public:
    glm::vec2 m_position;
    glm::vec2 m_velocity;
    int m_width;
    int m_height;
    int m_scale;

    TransformComponent(int f_posX, int f_posY, int f_velX, int f_velY, int f_w, int f_h, int f_s)
    {
      m_position = glm::vec2(f_posX, f_posY);
      m_velocity = glm::vec2(f_velX, f_velY);
      m_width    = f_w;
      m_height   = f_h;
      m_scale    = f_s;
    }

    void Initialize() override
    {
    }

    void Update(float f_deltaTime) override
    {
      m_position.x += m_velocity.x * f_deltaTime;
      m_position.y += m_velocity.y * f_deltaTime;
    }

    void Render() override {}

};

#endif
