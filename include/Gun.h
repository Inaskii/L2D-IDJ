#pragma once
#include "Sound.h"
class Character;

class Gun: public Component{
public:
  Gun(GameObject& associated, std::weak_ptr< GameObject>character);
  void Start();
  void Update(float dt);
  void Render();
  void Shoot(Vec2 target);
private:
  Sound shotSound;
  Sound reloadSound;
  enum cooldownState{ready, shoot, reload, pump};
  cooldownState state;
  Timer cdTimer;
  std::weak_ptr<GameObject> character;
  float angle;

};