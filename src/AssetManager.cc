#include "AssetManager.h"

AssetManager::AssetManager(EntityManager* f_manager) : manager(f_manager) {}

void AssetManager::ClearData()
{
  textures.clear();
}

void AssetManager::AddTexture(std::string f_textureId, const char* f_filePath)
{
  textures.emplace(f_textureId, TextureManager::LoadTexture(f_filePath));
}

SDL_Texture* AssetManager::GetTexture(std::string f_textureId)
{
  return textures[f_textureId];
}
