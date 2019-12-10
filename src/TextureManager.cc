#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* f_fileName)
{
  SDL_Surface* surface = IMG_Load(f_fileName);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::m_renderer, surface);
  SDL_FreeSurface(surface);

  return texture;
}

void TextureManager::Draw(SDL_Texture* f_texture, SDL_Rect f_sourceRectangle,
    SDL_Rect f_destinationRectangle, SDL_RendererFlip f_flip)
{
  SDL_RenderCopyEx(Game::m_renderer, f_texture, &f_sourceRectangle, &f_destinationRectangle, 0.0,
      NULL, f_flip);
}
