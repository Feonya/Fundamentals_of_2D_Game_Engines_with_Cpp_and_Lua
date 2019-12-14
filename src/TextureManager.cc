#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* f_fileName)
{
  SDL_Surface* l_surface = IMG_Load(f_fileName);
  SDL_Texture* l_texture = SDL_CreateTextureFromSurface(Game::renderer, l_surface);
  SDL_FreeSurface(l_surface);

  return l_texture;
}

void TextureManager::Draw(SDL_Texture* f_texture, SDL_Rect f_sourceRectangle,
    SDL_Rect f_destinationRectangle, SDL_RendererFlip f_flip)
{
  SDL_RenderCopyEx(Game::renderer, f_texture, &f_sourceRectangle, &f_destinationRectangle, 0.0,
      NULL, f_flip);
}
