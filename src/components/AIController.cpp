#include "../../include/AIController.h"
#include "../../include/Character.h"
#include "../../include/GameObject.h"
#include "../../include/Gun.h"
#include "../../include/Npc.h"
#include "../../include/SpriteRenderer.h"

int AIController::npcCounter = 0;

AIController::AIController(GameObject& associated)
  : Component(associated),
    state(RESTING),
    restTimer(),
    destination(0, 0)
{
npcCounter++;
}

AIController::~AIController(){npcCounter--;}

void AIController::Start(){}

bool AIController::ShootAt(const Vec2& target)
{
  Npc* npc = associated.GetComponent<Npc>();
  if (npc == nullptr) {
    return false;
  }

  auto weaponGO = npc->GetWeapon().lock();
  if (!weaponGO) {
    return false;
  }

  Gun* gun = weaponGO->GetComponent<Gun>();
  if (gun == nullptr) {
    return false;
  }

  return gun->Shoot(target);
}

void AIController::NotifyCollision(GameObject& other){}

void AIController::Update(float dt)
{
  Character* player = Character::player;
  if (associated.IsDead() || player == nullptr || player->IsDead()) {
    return;
  }

  const float restCooldown = 1.0f;
  const float moveSpeed = 30.0f;
  const float reachDistance = 900.0f;
  const Vec2 playerCenter = player->GetCenter();
  Npc* npc = associated.GetComponent<Npc>();
  Gun* gun = nullptr;
  if (npc != nullptr) {
    if (auto weaponGO = npc->GetWeapon().lock()) {
      gun = weaponGO->GetComponent<Gun>();
    }
  }

  if (gun != nullptr) {
    gun->Aim(playerCenter);
  }

  if (state == RESTING) {
    restTimer.Update(dt);
    if (restTimer.Get() > restCooldown) {
      state = MOVING;
      destination = playerCenter;
    }
    return;
  }

  destination = playerCenter;
  Vec2 center = associated.box.GetCenter();
  Vec2 dir = destination - center;

  if (Vec2::dist(center,destination) <= reachDistance) {
    if (ShootAt(destination)) {
      restTimer.Restart();
      state = RESTING;
    }
    return;
  }

  
  Vec2 displacement = dir.normalized() * moveSpeed * dt;
  associated.box.x += displacement.x;
  associated.box.y += displacement.y;

  if (SpriteRenderer* spriteRenderer = associated.GetComponent<SpriteRenderer>()) {
    spriteRenderer->FlipX(displacement.x > 0.0f);
  }
}

void AIController::Render()
{
}
