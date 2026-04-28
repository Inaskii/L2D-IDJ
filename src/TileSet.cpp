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
  rows = tileSet.GetHeigth()/tileHeight;
  col = tileSet.GetWidth()/tileWidth;
  tileCount = rows * col;
  

}
void TileSet::RenderTile(unsigned index, float x, float y){
  if(!(index >=0 && index<tileCount-1)) return;

  tileSet.SetClip(col*tileWidth,rows*tileHeight,tileWidth,tileHeight);  
  tileSet.Render(x,y,tileWidth,tileHeight);
}
int TileSet::GetTileWidth(){
  return tileWidth;
}
int TileSet::GetTileHeight(){
  return tileHeight;
}
