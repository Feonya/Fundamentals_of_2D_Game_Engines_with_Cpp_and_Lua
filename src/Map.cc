#include <fstream>
#include "EntityManager.h"
#include "components/TileComponent.h"
#include "Map.h"

extern EntityManager g_manager;

Map::Map(std::string f_textureId, int f_scale, int f_tileSize) :
    textureId(f_textureId), scale(f_scale), tileSize(f_tileSize) {}

void Map::LoadMap(std::string f_filePath, int f_mapSizeX, int f_mapSizeY)
{
  std::fstream l_mapFile;
  l_mapFile.open(f_filePath);

  for (int l_y = 0; l_y < f_mapSizeY; ++l_y)
    for (int l_x = 0; l_x < f_mapSizeX; ++l_x)
    {
      char l_ch;
      l_mapFile.get(l_ch);
      int l_sourceRectY = atoi(&l_ch) * tileSize;
      l_mapFile.get(l_ch);
      int l_sourceRectX = atoi(&l_ch) * tileSize;
      AddTile(l_sourceRectX, l_sourceRectY, l_x * tileSize * scale, l_y * tileSize * scale);
      l_mapFile.ignore();
    }

  l_mapFile.close();
}

void Map::AddTile(int f_sourceRectX, int f_sourceRectY, int f_x, int f_y)
{
  Entity& l_newTile(g_manager.AddEntity("tile", TILEMAP_LAYER));
  l_newTile.AddComponent<TileComponent>(f_sourceRectX, f_sourceRectY, f_x, f_y, tileSize, scale,
      textureId);
}
