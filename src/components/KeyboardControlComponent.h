#ifndef KEYBOARDCONTROLCOMPONENT_H
#define KEYBOARDCONTROLCOMPONENT_H

#include <string>
#include "TransformComponent.h"
#include "SpriteComponent.h"

class KeyboardControlComponent : public Component {
  public:
    std::string upKey;
    std::string rightKey;
    std::string downKey;
    std::string leftKey;
    std::string shootKey;
    TransformComponent* transform;
    SpriteComponent*    sprite;

    KeyboardControlComponent() {}

    KeyboardControlComponent(std::string f_upKey, std::string f_rightKey, std::string f_downKey,
        std::string f_leftKey, std::string f_shootKey)
    {
      upKey    = GetSDLKeyStringCode(f_upKey);
      rightKey = GetSDLKeyStringCode(f_rightKey);
      downKey  = GetSDLKeyStringCode(f_downKey);
      leftKey  = GetSDLKeyStringCode(f_leftKey);
      shootKey = GetSDLKeyStringCode(f_shootKey);
    }

    std::string GetSDLKeyStringCode(std::string f_key)
    {
      if (f_key.compare("up")    == 0) return "1073741906";
      if (f_key.compare("down")  == 0) return "1073741905";
      if (f_key.compare("left")  == 0) return "1073741904";
      if (f_key.compare("right") == 0) return "1073741903";
      if (f_key.compare("space") == 0) return "32";

      return std::to_string(static_cast<int>(f_key[0]));
    }

    void Initialize() override
    {
      transform = owner->GetComponent<TransformComponent>();
      sprite    = owner->GetComponent<SpriteComponent>();
    }

    void Update(float f_deltaTime) override
    {
      if (Game::event.type == SDL_KEYDOWN)
      {
        std::string l_keyCode = std::to_string(Game::event.key.keysym.sym);

        if (l_keyCode.compare(upKey) == 0)
        {
          transform->velocity.x = 0;
          transform->velocity.y = -100;
          sprite->Play("UpAnimation");
        }
        if (l_keyCode.compare(rightKey) == 0)
        {
          transform->velocity.x = 100;
          transform->velocity.y = 0;
          sprite->Play("RightAnimation");
        }
        if (l_keyCode.compare(downKey) == 0)
        {
          transform->velocity.x = 0;
          transform->velocity.y = 100;
          sprite->Play("DownAnimation");
        }
        if (l_keyCode.compare(leftKey) == 0)
        {
          transform->velocity.x = -100;
          transform->velocity.y = 0;
          sprite->Play("LeftAnimation");
        }
        if (l_keyCode.compare(shootKey) == 0)
        {
          // TODO
        }
      }

      if (Game::event.type == SDL_KEYUP)
      {
        std::string l_keyCode = std::to_string(Game::event.key.keysym.sym);

        if (l_keyCode.compare(upKey) == 0)
        {
          transform->velocity.y = 0;
        }
        if (l_keyCode.compare(rightKey) == 0)
        {
          transform->velocity.x = 0;
        }
        if (l_keyCode.compare(downKey) == 0)
        {
          transform->velocity.y = 0;
        }
        if (l_keyCode.compare(leftKey) == 0)
        {
          transform->velocity.x = 0;
        }
        if (l_keyCode.compare(shootKey) == 0)
        {
          // TODO
        }
      }
    }
};

#endif
