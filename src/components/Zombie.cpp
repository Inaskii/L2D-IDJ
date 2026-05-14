#include "../../include/Zombie.h"
#include "../../include/GameObject.h"
#include "../../include/Bullet.h"
#include "../../include/Character.h"
#include "../../include/Collider.h"
#include "../../include/SpriteRenderer.h"
#include "../../include/Animator.h"
#include "../../include/InputManager.h"
#include "../../include/Vec2.h"

int Zombie::zombieCount = 0;
float moveSpeed = 80;

Zombie::Zombie(GameObject& associated)
  : Component(associated),
    hitpoints(80),
    hit(false),
    dead(false),
    deathSound("Dead.wav"),
    hitSound("Hit0.wav")
  {

  SpriteRenderer* spriteRenderer = new SpriteRenderer(associated, "Enemy.png", 3, 2);
  associated.AddComponent(spriteRenderer);
  Animator* animator = new Animator(associated);
  associated.AddComponent(animator);
  animator->AddAnimation("walking",Animation(0,3,0.15f));
  animator->AddAnimation("dead",Animation(5,5,0));
  animator->AddAnimation("hit",Animation(4,4,0));
  animator->SetAnimation("walking"); 

  zombieCount++;
}

Zombie::~Zombie(){
  zombieCount--;
}

int Zombie::GetZombieCount(){
  return zombieCount;
}

bool Zombie::IsDead(){return dead;}

void Zombie::Start(){
  associated.AddComponent(new Collider(associated));
  associated.GetComponent<Animator>()->SetAnimation("walking");
}
void Zombie::Damage(int damage)
{
  if (dead) return;

  hitSound.Play(1);
  hitpoints -= damage;
  if(hitpoints<=0)
  {
    Die();
    return;
  }
  hit = true;
  hitTimer.Restart();
  associated.GetComponent<Animator>()->SetAnimation("hit");

}

void Zombie::Update(float dt)
{
  if (!dead) {
    if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
      float mx = InputManager::GetInstance().GetMouseX();
      float my = InputManager::GetInstance().GetMouseY();
      if (associated.box.Contains(mx, my)) {
        Damage(25);
      }
    }

    Character* player = Character::player;
    if (player != nullptr) {
      Vec2 playerCenter = player->GetCenter();
      Vec2 zombieCenter = associated.box.GetCenter();
      Vec2 direction = playerCenter - zombieCenter;
      if (direction.magnitude() > 0.0f) {
        direction.normalize();
        Vec2 displacement = direction * moveSpeed * dt;
        associated.box.x += displacement.x;
        associated.box.y += displacement.y;

        if (SpriteRenderer* spriteRenderer = associated.GetComponent<SpriteRenderer>()) {
          spriteRenderer->FlipX(displacement.x > 0.0f);
        }
      }
    }
    

    hitTimer.Update(dt);

    if(hit && hitTimer.Get() > 0.5f)
    {
      hit = false;
      associated.GetComponent<Animator>()->SetAnimation("walking");
    }
  } else {
    deathTimer.Update(dt);
    if (deathTimer.Get() > 5.0f) {
      associated.RequestDelete();
    }
  }
}

void Zombie::Die(){
  if (dead) return;
  dead = true;
  hit = false;
  deathTimer.Restart();
  if (Collider* collider = associated.GetComponent<Collider>()) {
    associated.RemoveComponent(collider);
  }
  associated.GetComponent<Animator>()->SetAnimation("dead");
  deathSound.Play(1);
}

void Zombie::Render()
{
}

void Zombie::NotifyCollision(GameObject& other)
{
  Bullet* bullet = other.GetComponent<Bullet>();
  if (bullet != nullptr) {
    Damage(bullet->GetDamage());
  }
}
