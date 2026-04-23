#include "../../include/Zombie.h"
#include "../../include/GameObject.h"
#include "../../include/SpriteRenderer.h"

Zombie::Zombie(GameObject& associated)
  : Component(associated),
    hitpoints(100)
{
  SpriteRenderer* spriteRenderer = new SpriteRenderer(associated, "img/Enemy.png", 3, 2);
  spriteRenderer->SetFrame(1);
  associated.AddComponent(spriteRenderer);
}

void Zombie::Damage(int damage)
{
  hitpoints -= damage;
  if(hitpoints<=0) associated.GetComponent<SpriteRenderer>()->SetFrame(5);
}

void Zombie::Update(float dt)
{
  Damage(1); 
}

void Zombie::Render()
{
}
