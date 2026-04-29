#include "../../include/TileMap.h"
#include "../../include/includes.h"


TileMap::TileMap(GameObject& associated, const std::string& file, TileSet* tileSet):
    Component(associated),
    tileSet(tileSet){
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
    this->tileSet.reset(tileSet);
}
int& TileMap::At(int x, int y, int z){

    return tileMatrix[ (z * mapWidth * mapHeight) + (y * mapWidth) + x];
}
void TileMap::Update(float dt){}

void TileMap::Render() {
    for(int i = 0; i < mapDepth; i++) RenderLayer(i);
}
void TileMap::RenderLayer(int layer){
	int realWidth = tileSet->GetTileWidth();
	int realHeight= tileSet->GetTileHeight();
	for(int i =0;i<mapWidth;i++)
	{
		for(int j =0;j<mapHeight;j++)
		{
			int at = At(i,j,layer);
			int posX = associated.box.x+ (i*realWidth), posY = associated.box.y+ (j*realHeight);
			tileSet->RenderTile(at,posX,posY);			
		}
	}
}

int TileMap::GetWidth(){return mapWidth;}
int TileMap::GetHeight(){return mapHeight;}
int TileMap::GetDepth(){return mapDepth;}
