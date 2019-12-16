#include "AssetManager.h"

AssetManager::AssetManager(EntityManager* f_manager) : manager(f_manager) {}

void AssetManager::ClearData()
{
  textures.clear();
  fonts.clear();
}

void AssetManager::AddTexture(std::string f_textureId, const char* f_filePath)
{
  textures.emplace(f_textureId, TextureManager::LoadTexture(f_filePath));
}

SDL_Texture* AssetManager::GetTexture(std::string f_textureId)
{
  return textures[f_textureId];
}

void AssetManager::AddFont(std::string f_fontId, const char* f_filePath, int f_fontSize)
{
  fonts.emplace(f_fontId, FontManager::LoadFont(f_filePath, f_fontSize));
}

TTF_Font* AssetManager::GetFont(std::string f_fontId)
{
  return fonts[f_fontId];
}
