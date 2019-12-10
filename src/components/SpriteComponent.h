#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "../AssetManager.h"
#include "../TextureManager.h"
#include "TransformComponent.h"

class SpriteComponent : public Component {
  public:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent(const char* f_filePath) { SetTexture(f_filePath); }

    void SetTexture(std::string f_assetTextureId)
    {
      m_texture = Game::assetManager->GetTexture(f_assetTextureId);
    }

    void Initialize() override
    {
      m_transform = owner->GetComponent<TransformComponent>();
      m_sourceRectangle.x = 0;
      m_sourceRectangle.y = 0;
      m_sourceRectangle.w = m_transform->width;
      m_sourceRectangle.h = m_transform->height;
    }

    void Update(float f_deltaTime) override
    {
      m_destinationRectangle.x = m_transform->position.x;
      m_destinationRectangle.y = m_transform->position.y;
      m_destinationRectangle.w = m_transform->width  * m_transform->scale;
      m_destinationRectangle.h = m_transform->height * m_transform->scale;
    }

    void Render()
    {
      TextureManager::Draw(m_texture, m_sourceRectangle, m_destinationRectangle, spriteFlip);
    }

  private:
    TransformComponent* m_transform;
    SDL_Texture* m_texture;
    SDL_Rect m_sourceRectangle;
    SDL_Rect m_destinationRectangle;
};

#endif