#include "../../include/TileMap.h"
#include "../../include/includes.h"


TileMap::TileMap(GameObject& associated, const std::string& file, TileSet* tileSet):
    Component(associated),
    tileSet(tileSet){
    Load(file);
		std::cout<<"End end mesmo\n";
}
void TileMap::Load(const std::string& fileName){
	std::ifstream file;
	
	file.open(fileName);
	if(!file.is_open()){
		std::cout<<"Erro ao abrir Tilemap " << fileName<< "\n";
	}
	std::cout<<"Tilemap carregar start\n";

	char comma;
	file >> mapWidth >> comma >> mapHeight >> comma >> mapDepth >> comma;
	tileMatrix.clear();
	int aux;
	int sz = mapWidth*mapHeight*mapDepth;
	for(int i = 0;i < sz;i++){
		file >> aux >> comma;
		// std::cout<<aux<<" ";
		tileMatrix.push_back(aux);

	}
	file.close();
	std::cout<<"Tilemap carregar end\n";
	
}
void TileMap::Start(){}
void TileMap::SetTileSet(TileSet* tileSet){
    this->tileSet.reset(tileSet);
}
int& TileMap::At(int x, int y, int z){

    return tileMatrix[(z * mapWidth * mapHeight) + (y * mapWidth) + x];
}
void TileMap::Update(float dt){}

void TileMap::RenderLayer(int layer){
	if(tileSet == nullptr) return;
	int realWidth = tileSet->GetTileWidth();
	int realHeight= tileSet->GetTileHeight();

	for(int x =0;x<mapWidth;x++){
		for(int y =0;y<mapHeight;y++){
			int at = At(x,y,layer);
			if(at < 0) continue;
			int posX = associated.box.x + (x*realWidth);
			int posY = associated.box.y + (y*realHeight);
			tileSet->RenderTile(at,posX,posY);			
		}
	}
}
void TileMap::Render() {
		for(int i = 0; i < mapDepth; i++) RenderLayer(i);
}

int TileMap::GetWidth(){return mapWidth;}
int TileMap::GetHeight(){return mapHeight;}
int TileMap::GetDepth(){return mapDepth;}
