#pragma once

#include "Component.h"
#include "GameObject.h"
#include "TileSet.h"
#include "includes.h"

class TileMap : public Component {
public:
    TileMap(GameObject& associated, const std::string& file = "", TileSet* tileSet = nullptr);
    void Load(const std::string& file);
    void SetTileSet(TileSet* tileSet);
    int& At(int x, int y, int z = 0);
    void Render();
    void NotifyCollision(GameObject& other);
    void Start();
    void Update(float dt);
    void RenderLayer(int layer);
    int GetWidth();
    int GetHeight();
    int GetDepth(); 
private:
    std::vector<int> tileMatrix;
    std::unique_ptr<TileSet> tileSet;
    int mapWidth;
    int mapHeight;
    int mapDepth;
};