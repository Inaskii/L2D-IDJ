#include "../include/TileSet.h"
#include "../include/includes.h"


TileSet::TileSet(int tileWidth, int tileHeight, std::string file):
  tileSet(file,1,1)
{
  std::cout<<"TileSetCarregar Start\n";
  this->tileWidth = tileWidth;
  this->tileHeight = tileHeight;

  tileSet.Open(file);
  if(!tileSet.isOpen()){
    std::cout<<"Erro ao abrir tileset\n";
    std::cout<<"Arquivo: "<<file<<"\n";
  }
  rows = tileSet.GetHeigth()/tileHeight;
  col = tileSet.GetWidth()/tileWidth;
  tileCount = rows * col;
  

  std::cout<<"TileSetCarregar End\n";
}
void TileSet::RenderTile(unsigned index, float x, float y){
  if(index >= (unsigned)tileCount){
    std::cout<<"Erro em Tileset::rendertile, index = " << index <<"\n";
    return;
  }

  int tilesPerRow = col;
  int rowIndex = index / tilesPerRow;
  int colIndex = index % tilesPerRow;
  tileSet.SetClip(colIndex * tileWidth, rowIndex * tileHeight, tileWidth, tileHeight);
  tileSet.Render(x, y, tileWidth, tileHeight);
}
int TileSet::GetTileWidth(){
  return tileWidth;
}
int TileSet::GetTileHeight(){
  return tileHeight;
}

bool TileSet::IsSolid(unsigned index) const{
  if(index >= (unsigned)tileCount) return false;

  int rowIndex = index / col;
  int colIndex = index % col;
  return (colIndex >= 0 && colIndex <= 2) && (rowIndex >= 3 && rowIndex <= 4);
}
