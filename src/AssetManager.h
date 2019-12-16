#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include <SDL2/SDL_ttf.h>
#include "TextureManager.h"
#include "FontManager.h"
#include "EntityManager.h"

class AssetManager {
  public:
    AssetManager(EntityManager* f_manager);
    ~AssetManager();

    void ClearData();

    void AddTexture(std::string f_textureId, const char* f_filePath);
    SDL_Texture* GetTexture(std::string f_textureId);

    void AddFont(std::string f_fontId, const char* f_filePath, int f_fontSize);
    TTF_Font* GetFont(std::string f_fontId);

  private:
    EntityManager* manager;
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, TTF_Font*>    fonts;
};

#endif
