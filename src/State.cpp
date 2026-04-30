#include "../include/State.h"
#include "../include/Sprite.h"
#include "../include/Music.h"
#include "../include/GameObject.h"
#include "../include/TileSet.h"
#include "../include/TileMap.h"
#include "../include/Game.h"
#define INCLUDE_SDL
#include "../include/SDL_include.h"
#include "../include/Zombie.h"
State::State()
  : sprite(),
    music(),
    quitRequested(false)
{
}
State::~State()
{
  objectArray.clear();
}
void State::LoadAssets()
{
  std::cout<<"LoaAssets start\n";
  GameObject* world = new GameObject();
  TileSet* tileSet = new TileSet(64,64,"Tileset.png");
  TileMap* tileMap = new TileMap(*world,"assets/map/map.txt",tileSet);
  std::cout<<"a ";
  world->AddComponent(tileMap); 
  std::cout<<"b "; 
  world->box.x = 0; world->box.y = 0;
  objectArray.emplace_back(world); 

  GameObject* zombie = new GameObject();
  Zombie* z = new Zombie(*zombie);
  zombie->AddComponent(z);
  zombie->box.x = 600;
  zombie->box.y = 450;
  objectArray.emplace_back(zombie);

  GameObject* zombie2 = new GameObject();
  Zombie* z2 = new Zombie(*zombie2);
  zombie2->AddComponent(z2);
  zombie2->box.x = 300;
  zombie2->box.y = 450;
  objectArray.emplace_back(zombie2);




  std::cout<<"LoaAssets end\n";
}


bool State::QuitRequested()
{
  return quitRequested;
}
void State::Update(float dt)
{
  if(SDL_QuitRequested())
  {
    quitRequested = true;
  }
  for (const std::unique_ptr<GameObject>& gameObject : objectArray)
  {
    gameObject->Update(dt);
  }
}
void State::Render()
{
  SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
  if (renderer == nullptr) {
    return;
  }

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  sprite.Render(0, 0, sprite.GetWidth(), sprite.GetHeigth());

  for (const std::unique_ptr<GameObject>& gameObject : objectArray)
  {
    gameObject->Render();
  }

  SDL_RenderPresent(renderer);
}
