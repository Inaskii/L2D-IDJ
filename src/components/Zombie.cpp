#include "../../include/Zombie.h"
#include "../../include/GameObject.h"
#include "../../include/SpriteRenderer.h"
#include "../../include/Animator.h"

Zombie::Zombie(GameObject& associated)
  : Component(associated),
    hitpoints(100),
    hit(0),
    sound("Dead.wav")
  {

  SpriteRenderer* spriteRenderer = new SpriteRenderer(associated, "Enemy.png", 3, 2);
  associated.AddComponent(spriteRenderer);
  Animator* animator = new Animator(associated);
  associated.AddComponent(animator);
  animator->AddAnimation("walking",Animation(0,3,10));
  animator->AddAnimation("dead",Animation(5,5,0));
  animator->AddAnimation("hit",Animation(4,4,0));
  animator->SetAnimation("walking"); 
}

void Zombie::Damage(int damage)
{
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
  hitTimer.Update(dt);
  Damage(1); 

}
void Zombie::Die(){
  associated.GetComponent<Animator>()->SetAnimation("dead");
  sound.Play(1);
}
void Zombie::Render()
{
}
