#ifndef TILECOMPONENT_H
#define TILECOMPONENT_H

#include <SDL2/SDL.h>
#include "../AssetManager.h"
#include <glm/glm.hpp>

class TileComponent : public Component {
  public:
    SDL_Texture* texture;
    SDL_Rect     sourceRectangle;
    SDL_Rect     destinationRectangle;
    glm::vec2    position;

    TileComponent(int f_sourceRectX, int f_sourceRectY, int f_x, int f_y, int f_tileSize,
        int f_tileScale, std::string f_assetTextureId)
    {
      texture = Game::assetManager->GetTexture(f_assetTextureId);

      sourceRectangle.x = f_sourceRectX;
      sourceRectangle.y = f_sourceRectY;
      sourceRectangle.w = f_tileSize;
      sourceRectangle.h = f_tileSize;

      destinationRectangle.x = f_x;
      destinationRectangle.y = f_y;
      destinationRectangle.w = f_tileSize * f_tileScale;
      destinationRectangle.h = f_tileSize * f_tileScale;

      position.x = f_x;
      position.y = f_y;
    }

    ~TileComponent() { SDL_DestroyTexture(texture); }

    void Update(float f_deltaTime) override
    {
      // TODO: Here is where we will take care of the tile positions
      //       based on the camera control that will keep moving around.
    }

    void Render() override
    {
      TextureManager::Draw(texture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
    }
};

#endif
