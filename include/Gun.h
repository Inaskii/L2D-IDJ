#pragma once
#include "Component.h"
#include "Timer.h"
#include "Vec2.h"
#include "includes.h"
#include "Sound.h"

class Gun: public Component{
public:
  Gun(GameObject& associated, std::weak_ptr<GameObject> owner, bool targetsPlayer = false);
  void Start();
  void Update(float dt);
  void Render();
  void NotifyCollision(GameObject& other);
  void Aim(Vec2 target);
  bool Shoot(Vec2 target);
private:
  Sound shotSound;
  Sound reloadSound;
  enum cooldownState{ready, shoot, reload, pump};
  cooldownState state;
  Timer cdTimer;
  std::weak_ptr<GameObject> owner;
  bool targetsPlayer;
  float angle;

};