#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include "TextureManager.h"
#include "EntityManager.h"

class AssetManager {
  public:
    AssetManager(EntityManager* f_manager);
    ~AssetManager();

    void ClearData();
    void AddTexture(std::string textureId, const char* filePath);
    SDL_Texture* GetTexture(std::string textureId);

  private:
    EntityManager* m_manager;
    std::map<std::string, SDL_Texture*> m_textures;
};

#endif
