#pragma once
#include "Component.h"
#include "Vec2.h"

class Bullet : public Component {
public:
  Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, bool targetsPlayer);
  void Start();
  void Update(float dt);
  void Render();
  bool targetsPlayer;
  void NotifyCollision(GameObject& other);
  int GetDamage();


private:
  float angle;
  float speed;
  float distanceLeft;
  int damage;
  Vec2 dir;
};
