#include "../../include/WaveSpawner.h"
#include "../../include/Game.h"
#include "../../include/State.h"
#include "../../include/Camera.h"
#include "../../include/GameObject.h"
#include "../../include/Npc.h"
#include "../../include/Zombie.h"


WaveSpawner::WaveSpawner(GameObject& associated):
Component(associated), zombieCounter(0), currentWave(0){
  Wave wave1(2,0.5f);
  Wave wave2(5,0.5f);
  Wave wave3(7,0.5f);
  waves = {wave1,wave2,wave3};
}

void WaveSpawner::Start(){}

void WaveSpawner::NotifyCollision(GameObject& other){}

void WaveSpawner::Update (float dt){
  zombieCooldownTimer.Update(dt);
  // std::cout<<zombieCooldownTimer.Get()<<"\n";

  if (currentWave >= (int)waves.size()) {
    associated.RequestDelete();
    return;
  }

  Wave& wave = waves[currentWave];
  if (zombieCounter < wave.zombies) {
    if (zombieCooldownTimer.Get() > wave.cooldown) {
      float angle = ((float)rand() / RAND_MAX) * 2.0f * M_PI;
      const float spawnDistance = 200.0f;
      Vec2 spawnPos = Camera::pos + Vec2(cos(angle), sin(angle)) * spawnDistance;

      if ((rand() % 10) == 0) Game::GetInstance().GetCurrentState().SpawnNPC(spawnPos.x,spawnPos.y);
      else Game::GetInstance().GetCurrentState().SpawnZombie(spawnPos.x,spawnPos.y);

      zombieCounter++;
      zombieCooldownTimer.Restart();
    }
  } else {
    if (Zombie::GetZombieCount() == 0) {
      std::cout<<"NOVA WAVE\n";
      currentWave++;
      zombieCounter = 0;
      if (currentWave >= (int)waves.size()) {
        associated.RequestDelete();
      }
    }
  }
}
void WaveSpawner::Render(){

}
