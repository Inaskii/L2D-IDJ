#pragma once
#include "Component.h"
#include <string>

class Zombie : public Component {
public:
  Zombie(GameObject& associated);
  void Damage(int damage);
  void Update(float dt);
  void Render();

private:
  int hitpoints;
};