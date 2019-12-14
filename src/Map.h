#ifndef MAP_H
#define MAP_H

#include <string>

class Map {
  public:
    Map(std::string f_textureId, int f_scale, int f_tileSize);
    ~Map();

    void LoadMap(std::string f_filePath, int f_mapSizeX, int f_mapSizeY);
    void AddTile(int f_sourceRectX, int f_sourceRectY, int f_x, int f_y);

  private:
    std::string textureId;
    int         scale;
    int         tileSize;
};

#endif
