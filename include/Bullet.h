#pragma once
#include "Component.h"
#include "Vec2.h"

class Bullet : public Component {
public:
  Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance);
  void Start();
  void Update(float dt);
  void Render();
  int GetDamage();

private:
  float angle;
  float speed;
  float distanceLeft;
  int damage;
  Vec2 dir;
};
