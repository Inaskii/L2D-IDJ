#pragma once
#include "Component.h"
#include "includes.h"
#include "Timer.h"
#include "Wave.h"

class WaveSpawner : public Component{
public:
  WaveSpawner(GameObject& associated);
  void Update (float dt);
  void Render();
  void Start();
  void NotifyCollision(GameObject& other);
private:
  int zombieCounter;
  std::vector<Wave> waves;
  Timer zombieCooldownTimer;
  int currentWave;
};