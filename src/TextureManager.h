#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "Game.h"

class TextureManager {
  public:
    static SDL_Texture* LoadTexture(const char* f_fileName);
    static void Draw(SDL_Texture* f_texture, SDL_Rect f_sourceRectangle,
        SDL_Rect f_destinationRectangle, SDL_RendererFlip f_flip);
};

#endif
