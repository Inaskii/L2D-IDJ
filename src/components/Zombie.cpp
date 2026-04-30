#include "../../include/Zombie.h"
#include "../../include/GameObject.h"
#include "../../include/SpriteRenderer.h"
#include "../../include/Animator.h"

Zombie::Zombie(GameObject& associated)
  : Component(associated),
    hitpoints(100),
    sound("Dead.wav")
  {

  SpriteRenderer* spriteRenderer = new SpriteRenderer(associated, "Enemy.png", 3, 2);
  associated.AddComponent(spriteRenderer);
  Animator* animator = new Animator(associated);
  associated.AddComponent(animator);
  animator->AddAnimation("walking",Animation(0,3,10));
  animator->AddAnimation("dead",Animation(5,5,0));
  animator->SetAnimation("walking"); 
}

void Zombie::Damage(int damage)
{
  hitpoints -= damage;

}

void Zombie::Update(float dt)
{
  Damage(1); 
  if(hitpoints<=0) Die();

}
void Zombie::Die(){
  associated.GetComponent<Animator>()->SetAnimation("dead");
  sound.Play(1);
}
void Zombie::Render()
{
}
