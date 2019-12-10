#include "AssetManager.h"

AssetManager::AssetManager(EntityManager* f_manager) : m_manager(f_manager) {}

void AssetManager::ClearData()
{
  m_textures.clear();
}

void AssetManager::AddTexture(std::string f_textureId, const char* f_filePath)
{
  m_textures.emplace(f_textureId, TextureManager::LoadTexture(f_filePath));
}

SDL_Texture* AssetManager::GetTexture(std::string f_textureId)
{
  return m_textures[f_textureId];
}
