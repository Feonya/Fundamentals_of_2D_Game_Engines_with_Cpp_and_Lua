#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "../AssetManager.h"
#include "../TextureManager.h"
#include "../Animation.h"
#include "TransformComponent.h"

class SpriteComponent : public Component {
  public:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent(std::string f_assetTextureId)
    {
      isAnimated = false;
      isFixed    = false;
      SetTexture(f_assetTextureId);
    }

    SpriteComponent(std::string f_id, int f_numFrames, int f_animationSpeed, bool f_hasDirections,
        bool f_isFixed) :
        numFrames(f_numFrames), aniamtionSpeed(f_animationSpeed), isFixed(f_isFixed)
    {
      isAnimated = true;

      if (f_hasDirections)
      {
        Animation l_downAnimation (0, f_numFrames, f_animationSpeed);
        Animation l_rightAnimation(1, f_numFrames, f_animationSpeed);
        Animation l_leftAnimation (2, f_numFrames, f_animationSpeed);
        Animation l_upAnimation   (3, f_numFrames, f_animationSpeed);

        animations.emplace("DownAnimation" , l_downAnimation);
        animations.emplace("RightAnimation", l_rightAnimation);
        animations.emplace("LeftAnimation" , l_leftAnimation);
        animations.emplace("UpAnimation"   , l_upAnimation);

        currentAnimationName = "DownAnimation";
        animationIndex = 0;
      }
      else
      {
        Animation l_singleAnimation(0, f_numFrames, f_animationSpeed);
        animations.emplace("SingleAnimation", l_singleAnimation);
        currentAnimationName = "SingleAnimation";
        animationIndex = 0;
      }

      Play(currentAnimationName);

      SetTexture(f_id);
    }

    void Play(std::string f_animationName)
    {
      numFrames            = animations[f_animationName].numFrames;
      animationIndex       = animations[f_animationName].index;
      aniamtionSpeed       = animations[f_animationName].animationSpeed;
      currentAnimationName = f_animationName;
    }

    void SetTexture(std::string f_assetTextureId)
    {
      texture = Game::assetManager->GetTexture(f_assetTextureId);
    }

    void Initialize() override
    {
      transform = owner->GetComponent<TransformComponent>();
      sourceRectangle.x = 0;
      sourceRectangle.y = 0;
      sourceRectangle.w = transform->width;
      sourceRectangle.h = transform->height;
    }

    void Update(float f_deltaTime) override
    {
      if (isAnimated)
        sourceRectangle.x =
            static_cast<int>(SDL_GetTicks() / aniamtionSpeed) % numFrames * sourceRectangle.w;
      sourceRectangle.y = animationIndex * transform->height;

      destinationRectangle.x = static_cast<int>(transform->position.x);
      destinationRectangle.y = static_cast<int>(transform->position.y);
      destinationRectangle.w = transform->width  * transform->scale;
      destinationRectangle.h = transform->height * transform->scale;
    }

    void Render()
    {
      TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
    }

  private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect     sourceRectangle;
    SDL_Rect     destinationRectangle;

    bool isAnimated;
    int  numFrames;
    int  aniamtionSpeed;
    bool isFixed;
    std::map<std::string, Animation> animations;
    std::string                      currentAnimationName;
    unsigned                         animationIndex = 0;
};

#endif
