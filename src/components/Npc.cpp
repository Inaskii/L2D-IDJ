#include "../../include/Game.h"
#include "../../include/Gun.h"
#include "../../include/Npc.h"

Npc::Npc(GameObject& associated)
  : Component(associated),
    hitpoints(30),
    hit(false),
    dead(false),
    deathSound("Dead.wav"),
    hitSound("Hit0.wav")
{
  SpriteRenderer* spriteRenderer = new SpriteRenderer(associated, "NPC.png",3,4);
  associated.AddComponent(spriteRenderer);

  associated.AddComponent(new AIController(associated));
  
  Animator* animator = new Animator(associated);
  associated.AddComponent(animator);    
  animator->AddAnimation("hit",Animation(9,9,0));
  animator->AddAnimation("walking",Animation(0,8,0.2f));
  animator->AddAnimation("dead",Animation(10,11,0));

  animator->SetAnimation("walking"); 

}

Npc::~Npc(){}

void Npc::Start(){
  associated.AddComponent(new Collider(associated));

  auto weaponGO = std::make_shared<GameObject>();
  auto owner = Game::GetInstance().GetCurrentState().GetObjectPtr(&associated);
  weaponGO->AddComponent(new Gun(*weaponGO, owner, true));
  weapon = Game::GetInstance().GetCurrentState().AddObject(weaponGO);
}

std::weak_ptr<GameObject> Npc::GetWeapon()
{
  return weapon;
}

bool Npc::IsDead(){return dead;}

void Npc::Damage(int damage){
  if (dead) return;

  hitSound.Play(1);
  hitpoints -= damage;
  if (hitpoints <= 0)
  {
    Die();
    return;
  }

  hit = true;
  hitTimer.Restart();
}

void Npc::Update(float dt)
{
  if (dead) {
    deathTimer.Update(dt);
    if (deathTimer.Get() > 5.0f) {
      associated.RequestDelete();
    }
    return;
  }

  hitTimer.Update(dt);

  if (hit && hitTimer.Get() > 0.5f){
    hit = false;
    associated.GetComponent<Animator>()->SetAnimation("walking");
  } 
}

void Npc::Die(){
  if (dead) return;
  dead = true;
  hit = false;
  deathTimer.Restart();
  if (Collider* collider = associated.GetComponent<Collider>()) {
    associated.RemoveComponent(collider);
  }
  if (auto weaponGO = weapon.lock()) {
    weaponGO->RequestDelete();
  }
  associated.GetComponent<Animator>()->SetAnimation("dead");
  deathSound.Play(1);
}

void Npc::Render(){}

void Npc::NotifyCollision(GameObject& other)
{
  Bullet* bullet = other.GetComponent<Bullet>();
  if (bullet != nullptr && !bullet->targetsPlayer) {
    Damage(bullet->GetDamage());
  }
}