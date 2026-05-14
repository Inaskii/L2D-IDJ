#pragma once
#include "includes.h"
#include "Sprite.h"
#include "Music.h"
#include "Game.h"
#include "SDL_include.h"
#include "Camera.h"
#include "Zombie.h"
#include "WaveSpawner.h"

class GameObject;

class State{
public:
  State();
  ~State();
  std::weak_ptr<GameObject> AddObject(std::shared_ptr<GameObject> go);
  std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
  bool QuitRequested();
  void LoadAssets();
  
  void Start();
  void Update(float dt);
  void Render();

  void SpawnZombie(int x, int y);
  void SpawnNPC(int x, int y);

private:
  bool started; 
  Sprite sprite;
  Music music;
  bool quitRequested;
  std::vector<std::shared_ptr<GameObject>> objectArray;
};