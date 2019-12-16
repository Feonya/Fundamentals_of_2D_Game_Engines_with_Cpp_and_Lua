#ifndef TEXTLABELCOMPONENT_H
#define TEXTLABELCOMPONENT_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../AssetManager.h"
#include "../Game.h"

class TextLabelComponent : public Component {
  public:
    TextLabelComponent(int f_x, int f_y, std::string f_text, std::string f_fontFamily,
        const SDL_Color& f_color)
    {
      position.x = f_x;
      position.y = f_y;
      text       = f_text;
      fontFamily = f_fontFamily;
      color      = f_color;
      SetLabelText(text, fontFamily);
    }

    void SetLabelText(std::string f_text, std::string f_fontFamily)
    {
      SDL_Surface* l_surface = TTF_RenderText_Blended(Game::assetManager->GetFont(f_fontFamily),
          f_text.c_str(), color);
      texture = SDL_CreateTextureFromSurface(Game::renderer, l_surface);
      SDL_FreeSurface(l_surface);
      SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
    }

    void Render() override
    {
      FontManager::Draw(texture, position);
    }

  private:
    SDL_Rect     position;
    std::string  text;
    std::string  fontFamily;
    SDL_Color    color;
    SDL_Texture* texture;
};

#endif
