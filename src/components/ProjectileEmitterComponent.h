#ifndef PROJECTILEEMITTERCOMPONENT_H
#define PROJECTILEEMITTERCOMPONENT_H

#include <glm/glm.hpp>
#include "TransformComponent.h"

class ProjectileEmitterComponent : public Component {
  public:
    ProjectileEmitterComponent(int f_speed, int f_angleDeg, int f_range, bool f_shouldLoop) :
        speed(f_speed), range(f_range), shouldLoop(f_shouldLoop) 
  {
    angleRad = glm::radians(static_cast<float>(f_angleDeg));
  }

  void Initialize() override
  {
    transform = owner->GetComponent<TransformComponent>();
    origin = glm::vec2(transform->position.x, transform->position.y);
    transform->velocity = glm::vec2(glm::cos(angleRad)*speed, glm::sin(angleRad)*speed);
  }

  void Update(float f_deltaTime) override
  {
    if (glm::distance(origin, transform->position) > range)
    {
      if (shouldLoop) transform->position = origin;
      else            owner->Destroy();
    }
  }
    
  private:
    TransformComponent* transform;
    glm::vec2           origin;
    int   speed;
    float angleRad;
    int   range;
    bool  shouldLoop;
};

#endif
