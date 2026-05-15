#pragma once
#include "includes.h"
#include "Sprite.h"

class TileSet{
  public:
    TileSet(int tileWidth, int tileHeight, std::string file);
    void RenderTile(unsigned index, float x, float y);
    int GetTileWidth();
    int GetTileHeight();
    bool IsSolid(unsigned index) const;
private:
  Sprite tileSet;
  int tileWidth;
  int tileHeight;
  int tileCount;
  int rows;
  int col;
  };