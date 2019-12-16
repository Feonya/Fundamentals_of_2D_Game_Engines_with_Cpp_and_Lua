#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class FontManager {
  public:
    static TTF_Font* LoadFont(const char* f_fileName, int f_fontSize);
    static void Draw(SDL_Texture* f_texture, SDL_Rect f_position);
};

#endif
