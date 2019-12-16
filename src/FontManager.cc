#include "Game.h"
#include "FontManager.h"

TTF_Font* FontManager::LoadFont(const char* f_fileName, int f_fontSize)
{
  return TTF_OpenFont(f_fileName, f_fontSize);
}

void FontManager::Draw(SDL_Texture* f_texture, SDL_Rect f_position)
{
  SDL_RenderCopy(Game::renderer, f_texture, NULL, &f_position);
}
