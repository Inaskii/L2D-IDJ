#include "../include/TileSet.h"
#include "../include/includes.h"


TileSet::TileSet(int tileWidth, int tileHeight, std::string file):
  tileSet(file,1,1)
{
  this->tileWidth = tileWidth;
  this->tileHeight = tileHeight;

  tileSet.Open(file);
  if(!tileSet.isOpen()){
    std::cout<<"Erro ao abrir tileset\n";
    std::cout<<"Arquivo: "<<file<<"\n";
  }
  int rows = tileSet.GetHeigth()/tileHeight;
  int columns = tileSet.GetWidth()/tileWidth;
  tileCount = rows * columns;

}
void RenderTile(unsigned index, float x, float y){
  
}
int GetTileWidth(){

}
int GetTileHeight(){

}
