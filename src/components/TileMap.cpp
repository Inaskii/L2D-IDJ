#include "../../include/TileMap.h"
#include "../../include/includes.h"


TileMap::TileMap(GameObject& associated, const std::string& file, TileSet* tileSet):
    Component(associated),
    tileSet(tileSet)
{
    Load(file);

}
void TileMap::Load(const std::string& fileName){
    std::ifstream file;
	
	file.open(fileName);
	file >> mapWidth;
	file >> mapHeight;
	file >> mapDepth;
	
    tileMatrix.clear();
	int aux;
	int sz = mapWidth*mapHeight*mapDepth;
    for(int i = 0;i < sz;i++){
		file >> aux;
		tileMatrix.push_back(aux-1);
	}
    file.close();
	
}
void TileMap::SetTileSet(TileSet* tileSet){

}
int& TileMap::At(int x, int y, int z = 0){

}
void TileMap::Render() {

}
void TileMap::RenderLayer(int layer){

}

int TileMap::GetWidth(){return mapWidth;}
int TileMap::GetHeight(){return mapHeight;}
int TileMap::GetDepth(){return mapDepth;}
