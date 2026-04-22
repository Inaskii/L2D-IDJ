#pragma once
#include "includes.h"
#include "Sprite.h"
#include "Music.h"

class GameObject;

class State{
public:
  State();
  ~State();
  void AddObject(GameObject go);
  bool QuitRequested();
  void LoadAssets();
  void Update(float dt);
  void Render();

private:
  Sprite sprite;
  Music music;
  bool quitRequested;
  std::vector<std::unique_ptr<GameObject>> objectArray;
};