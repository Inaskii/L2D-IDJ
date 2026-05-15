#include "../include/State.h"
#include "../include/GameObject.h"
#include "../include/Npc.h"
#include "../include/Zombie.h"

State::State()
  : popRequested(false),
    quitRequested(false),
    started(false){
}

State::~State(){
  objectArray.clear();
}

void State::StartArray(){
  for (size_t i = 0; i < objectArray.size(); i++){
    objectArray[i]->Start();
  }

  started = true;
}

void State::UpdateArray(float dt){
  const size_t objectCount = objectArray.size();
  for (size_t i = 0; i < objectCount; i++){
    objectArray[i]->Update(dt);
  }

  for (auto it = objectArray.begin(); it != objectArray.end();){
    if ((*it)->IsDead()) {
      it = objectArray.erase(it);
    } else {
      it++;
    }
  }
}

void State::RenderArray(){
  for (const std::shared_ptr<GameObject>& gameObject : objectArray){
    gameObject->Render();
  }
}

bool State::PopRequested(){
  return popRequested;
}

bool State::QuitRequested(){return quitRequested;}

std::weak_ptr<GameObject> State::AddObject(std::shared_ptr<GameObject> go){
  objectArray.emplace_back(go);
  if (started) {
    go->Start();
  }
  return std::weak_ptr<GameObject>(go);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go){
  std::weak_ptr<GameObject> ret;
  for (std::shared_ptr<GameObject>& obj : objectArray) {
    if (obj.get() == go) {
      ret = std::weak_ptr<GameObject>(obj);
      break;
    }
  }
  return ret;
}

bool State::IsTileBlocked(const Rect& box) const
{
  (void)box;
  return false;
}

void State::SpawnZombie(int x, int y){
  GameObject* zombieGO = new GameObject();
  zombieGO->box.x = x;
  zombieGO->box.y = y;

  Zombie* zombie = new Zombie(*zombieGO);
  zombieGO->AddComponent(zombie);

  AddObject(std::shared_ptr<GameObject>(zombieGO));
}

void State::SpawnNPC(int x, int y){
  GameObject* npcGO = new GameObject();
  npcGO->box.x = x;
  npcGO->box.y = y;
  npcGO->AddComponent(new Npc(*npcGO));

  AddObject(std::shared_ptr<GameObject>(npcGO));
}
