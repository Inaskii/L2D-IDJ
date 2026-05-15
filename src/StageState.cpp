#include "../include/GameData.h"
#include "../include/StageState.h"
#include "../include/Game.h"
#include "../include/Camera.h"
#include "../include/GameObject.h"
#include "../include/TileSet.h"
#include "../include/TileMap.h"
#include "../include/InputManager.h"
#include "../include/PlayerController.h"
#include "../include/SpriteRenderer.h"
#include "../include/Character.h"
#include "../include/Collider.h"
#include "../include/Collision.h"
#include "../include/EndState.h"
#include "../include/Npc.h"
#include "../include/WaveSpawner.h"
#include "../include/AIController.h"
#include "../include/Zombie.h"

StageState::StageState()
  : tileMap(nullptr),
    waveSpawner(),
    ending(false)
{
}

StageState::~StageState()
{
}

void StageState::Start()
{
  LoadAssets();
  StartArray();
}

void StageState::Pause()
{
}

void StageState::Resume()
{
}

void StageState::Update(float dt)
{
  if (ending) {
    return;
  }

  Camera::Update(dt);

  if (InputManager::GetInstance().QuitRequested()) {
    quitRequested = true;
  } else if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
    popRequested = true;
  }

  if (InputManager::GetInstance().KeyPress(SPACE_KEY)) {
    SpawnZombie(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());
  }

  UpdateArray(dt);

  for (size_t i = 0; i < objectArray.size(); i++)
  {
    auto objA = objectArray[i];
    auto a = objA->GetComponent<Collider>();
    if (!a) continue;

    for (size_t j = i + 1; j < objectArray.size(); j++)
    {
      auto objB = objectArray[j];
      auto b = objB->GetComponent<Collider>();
      if (!b) continue;

      if (Collision::IsColliding(a->box, b->box, objA->rotation, objB->rotation))
      {
        objA->NotifyCollision(*objB);
        objB->NotifyCollision(*objA);
      }
    }
  }

  if (Character::player != nullptr && Character::player->IsDead()) {
    TriggerEnd(false);
  } else if (waveSpawner.expired()) {
    TriggerEnd(true);
  }
}

void StageState::Render()
{
  SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
  if (renderer == nullptr) {
    return;
  }

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  sprite.Render(0, 0, sprite.GetWidth(), sprite.GetHeigth());
  RenderArray();
  SDL_RenderPresent(renderer);
}

void StageState::SpawnZombie(int x, int y)
{
  GameObject* zombieGO = new GameObject();
  zombieGO->box.x = x;
  zombieGO->box.y = y;

  Zombie* zombie = new Zombie(*zombieGO);
  zombieGO->AddComponent(zombie);

  AddObject(std::shared_ptr<GameObject>(zombieGO));
}

void StageState::SpawnNPC(int x, int y)
{
  GameObject* npcGO = new GameObject();
  npcGO->box.x = x;
  npcGO->box.y = y;
  npcGO->AddComponent(new Npc(*npcGO));

  AddObject(std::shared_ptr<GameObject>(npcGO));
}

void StageState::LoadAssets()
{
  GameObject* world = new GameObject();

  sprite.Open("Background.png");
  sprite.setFrame(0);
  sprite.cameraFollower = 1;

  TileSet* tileSet = new TileSet(64, 64, "Tileset.png");
  tileMap = new TileMap(*world, "assets/map/map.txt", tileSet);

  world->AddComponent(tileMap);
  world->box.x = 0;
  world->box.y = 0;
  AddObject(std::shared_ptr<GameObject>(world));

  GameObject* characterGO = new GameObject();
  characterGO->box.x = 1280;
  characterGO->box.y = 1280;
  AddObject(std::shared_ptr<GameObject>(characterGO));

  PlayerController* playerController = new PlayerController(*characterGO);
  Character* character = new Character(*characterGO, "Player.png");
  characterGO->AddComponent(character);
  characterGO->AddComponent(playerController);
  Camera::Follow(characterGO);

  GameObject* npcGO = new GameObject();
  npcGO->box.x = 1500;
  npcGO->box.y = 1280;
  npcGO->AddComponent(new Npc(*npcGO));
  AddObject(std::shared_ptr<GameObject>(npcGO));

  GameObject* waveSpawnerGO = new GameObject();
  waveSpawnerGO->AddComponent(new WaveSpawner(*waveSpawnerGO));
  waveSpawner = AddObject(std::shared_ptr<GameObject>(waveSpawnerGO));
}

bool StageState::IsTileBlocked(const Rect& box) const
{
  if (tileMap == nullptr) {
    return false;
  }

  return tileMap->IsBlocked(box);
}

void StageState::TriggerEnd(bool playerVictory)
{
  if (ending) {
    return;
  }

  ending = true;
  GameData::playerVictory = playerVictory;
  popRequested = true;
  Game::GetInstance().Push(new EndState());
}