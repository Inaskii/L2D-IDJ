#include "../include/State.h"
#include "../include/Sprite.h"
#include "../include/Music.h"
#include "../include/GameObject.h"
#include "../include/TileSet.h"
#include "../include/TileMap.h"
#include "../include/InputManager.h"
#include "../include/SpriteRenderer.h"
#define INCLUDE_SDL

State::State()
  : sprite(),
    music(),
    started(false),
    quitRequested(false)
{
}
State::~State()
{
  objectArray.clear();
}

void State::Start()
{
  LoadAssets();
  for(auto ptr: objectArray)
  {
    ptr->Start();
  }



  started = true;
}

void State::LoadAssets()
{
  std::cout<<"LoaAssets start\n";
  GameObject* world = new GameObject();

  sprite.Open("Background.png");
  sprite.setFrame(0);
  sprite.cameraFollower = 1;

  TileSet* tileSet = new TileSet(64,64,"Tileset.png");
  TileMap* tileMap = new TileMap(*world,"assets/map/map.txt",tileSet);
  
  world->AddComponent(tileMap); 
  world->box.x = 0; world->box.y = 0;
  objectArray.emplace_back(world); 



  std::cout<<"LoaAssets end\n";
}


bool State::QuitRequested()
{
  return quitRequested;
}
void State::Update(float dt){
  Camera::Update(dt);


  if (InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
    quitRequested = true;
  }

  if (InputManager::GetInstance().KeyPress(SPACE_KEY)) {
    SpawnZombie(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());
  }

  for (const std::shared_ptr<GameObject>& gameObject : objectArray)
  {
    gameObject->Update(dt);
  }
  for(int i =0;i<objectArray.size();i++)
  {
    if(objectArray[i]->IsDead())
    {
      objectArray.erase(objectArray.begin()+i);
      i--;
    }
  }
}

void State::SpawnZombie(int x, int y)
{
  GameObject* zombieGO = new GameObject();

  zombieGO->box.x = x;
  zombieGO->box.y = y;

  Zombie* zombie = new Zombie(*zombieGO);
  zombieGO->AddComponent(zombie);

  objectArray.emplace_back(zombieGO);
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

  for (const std::shared_ptr<GameObject>& gameObject : objectArray)
  {
    gameObject->Render();
  }

  SDL_RenderPresent(renderer);
}
