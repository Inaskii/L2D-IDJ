#pragma once
#include "Component.h"
#include "includes.h"
#include "Sound.h"
#include "Timer.h"



class Zombie : public Component {
public:
  Zombie(GameObject& associated);
  void Damage(int damage);
  void Update(float dt);
  void Render();
  void Die();
private:
  Sound sound;
  bool hit;
  int hitpoints;
  Timer hitTimer;
};