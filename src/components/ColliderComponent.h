#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <string>
#include <SDL2/SDL.h>
#include "TransformComponent.h"
#include "SpriteComponent.h"

class ColliderComponent : public Component {
  public:
    std::string  colliderTag;
    SDL_Rect     collider;
    SDL_Rect     sourceRectangle;
    SDL_Rect     destinationRectangle;
    TransformComponent* transform;

    ColliderComponent(std::string f_colliderTag, int f_x, int f_y, int f_width, int f_height,
        bool f_isShown) : colliderTag(f_colliderTag), isShown(f_isShown)
    {
      collider = {f_x, f_y, f_width, f_height};

      if (isShown) colliderTexture = Game::assetManager->GetTexture("collider-image");
    }

    void Initialize() override
    {
      if (owner->HasComponent<TransformComponent>())
      {
        transform = owner->GetComponent<TransformComponent>();
        sourceRectangle      = {0         , 0         , transform->width, transform->height};
        destinationRectangle = {collider.x, collider.y, collider.w      , collider.h};
      }
    }

    void Update(float f_deltaTime) override
    {
      collider.x = static_cast<int>(transform->position.x);
      collider.y = static_cast<int>(transform->position.y);
      collider.w = transform->width  * transform->scale;
      collider.h = transform->height * transform->scale;

      destinationRectangle.x = collider.x - Game::camera.x;
      destinationRectangle.y = collider.y - Game::camera.y;
    }

    void Render() override
    {
      if (isShown)
        TextureManager::Draw(colliderTexture, sourceRectangle, destinationRectangle,
            SDL_FLIP_NONE);
    }

  private:
    bool isShown;
    SDL_Texture* colliderTexture;
};

#endif
