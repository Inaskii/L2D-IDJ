#include "../../include/Zombie.h"
#include "../../include/GameObject.h"
#include "../../include/Bullet.h"
#include "../../include/Collider.h"
#include "../../include/SpriteRenderer.h"
#include "../../include/Animator.h"
#include "../../include/InputManager.h"
#include "../../include/Vec2.h"

Zombie::Zombie(GameObject& associated)
  : Component(associated),
    hitpoints(100),
    hit(false),
    dead(false),
    deathSound("Dead.wav"),
    hitSound("Hit0.wav")
  {

  SpriteRenderer* spriteRenderer = new SpriteRenderer(associated, "Enemy.png", 3, 2);
  associated.AddComponent(spriteRenderer);
  Collider* collider = new Collider(associated);
  associated.AddComponent(collider);
  Animator* animator = new Animator(associated);
  associated.AddComponent(animator);
  animator->AddAnimation("walking",Animation(0,3,0.15f));
  animator->AddAnimation("dead",Animation(5,5,0));
  animator->AddAnimation("hit",Animation(4,4,0));
  animator->SetAnimation("walking"); 
}
void Zombie::Start(){}
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
