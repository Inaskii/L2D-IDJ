#pragma once
#include "AIController.h"
#include "Bullet.h"
#include "Collider.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Component.h"
#include "includes.h"
#include "Sound.h"
#include "Timer.h"

class Npc : public Component {
public:
  Npc(GameObject& associated);
  ~Npc();
  void Damage(int damage);
  void Start();
  void Update(float dt);
  void Render();
  void NotifyCollision(GameObject& other);
  void Die();
  std::weak_ptr<GameObject> GetWeapon();
  bool IsDead();
private:
  Sound hitSound, deathSound;
  bool hit;
  bool dead;
  int hitpoints;
  Timer hitTimer;
  Timer deathTimer;
  std::weak_ptr<GameObject> weapon;
};