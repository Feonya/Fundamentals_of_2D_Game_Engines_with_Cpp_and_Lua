#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "../AssetManager.h"
#include "../TextureManager.h"
#include "../Animation.h"
#include "TransformComponent.h"

class SpriteComponent : public Component {
  public:
    SDL_RendererFlip m_spriteFlip = SDL_FLIP_NONE;

    SpriteComponent(std::string f_assetTextureId)
    {
      m_isAnimated = false;
      m_isFixed    = false;
      SetTexture(f_assetTextureId);
    }

    SpriteComponent(std::string f_id, int f_numFrames, int f_animationSpeed, bool f_hasDirections,
        bool f_isFixed) :
        m_numFrames(f_numFrames), m_animationSpeed(f_animationSpeed), m_isFixed(f_isFixed)
    {
      m_isAnimated = true;

      if (f_hasDirections)
      {
        Animation downAnimation (0, f_numFrames, f_animationSpeed);
        Animation rightAnimation(1, f_numFrames, f_animationSpeed);
        Animation leftAnimation (2, f_numFrames, f_animationSpeed);
        Animation upAnimation   (3, f_numFrames, f_animationSpeed);

        m_animations.emplace("DownAnimation" , downAnimation);
        m_animations.emplace("RightAnimation", rightAnimation);
        m_animations.emplace("LeftAnimation" , leftAnimation);
        m_animations.emplace("UpAnimation"   , upAnimation);

        m_currentAnimationName = "DownAnimation";
        m_animationIndex = 0;
      }
      else
      {
        Animation singleAnimation(0, f_numFrames, f_animationSpeed);
        m_animations.emplace("SingleAnimation", singleAnimation);
        m_currentAnimationName = "SingleAnimation";
        m_animationIndex = 0;
      }

      Play(m_currentAnimationName);

      SetTexture(f_id);
    }

    void Play(std::string f_animationName)
    {
      m_numFrames            = m_animations[f_animationName].m_numFrames;
      m_animationIndex       = m_animations[f_animationName].m_index;
      m_animationSpeed       = m_animations[f_animationName].m_animationSpeed;
      m_currentAnimationName = f_animationName;
    }

    void SetTexture(std::string f_assetTextureId)
    {
      m_texture = Game::m_assetManager->GetTexture(f_assetTextureId);
    }

    void Initialize() override
    {
      m_transform = m_owner->GetComponent<TransformComponent>();
      m_sourceRectangle.x = 0;
      m_sourceRectangle.y = 0;
      m_sourceRectangle.w = m_transform->m_width;
      m_sourceRectangle.h = m_transform->m_height;
    }

    void Update(float f_deltaTime) override
    {
      if (m_isAnimated)
        m_sourceRectangle.x =
            static_cast<int>(SDL_GetTicks() / m_animationSpeed) % m_numFrames * m_sourceRectangle.w;
      m_sourceRectangle.y = m_animationIndex * m_transform->m_height;

      m_destinationRectangle.x = static_cast<int>(m_transform->m_position.x);
      m_destinationRectangle.y = static_cast<int>(m_transform->m_position.y);
      m_destinationRectangle.w = m_transform->m_width  * m_transform->m_scale;
      m_destinationRectangle.h = m_transform->m_height * m_transform->m_scale;
    }

    void Render()
    {
      TextureManager::Draw(m_texture, m_sourceRectangle, m_destinationRectangle, m_spriteFlip);
    }

  private:
    TransformComponent* m_transform;
    SDL_Texture* m_texture;
    SDL_Rect     m_sourceRectangle;
    SDL_Rect     m_destinationRectangle;

    bool m_isAnimated;
    int  m_numFrames;
    int  m_animationSpeed;
    bool m_isFixed;
    std::map<std::string, Animation> m_animations;
    std::string                      m_currentAnimationName;
    unsigned                         m_animationIndex = 0;
};

#endif
