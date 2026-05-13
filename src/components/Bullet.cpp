#include "../../include/Bullet.h"
#include "../../include/GameObject.h"
#include "../../include/Collider.h"
#include "../../include/SpriteRenderer.h"
#include "../../include/Zombie.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, bool targetsPlayer)
  : Component(associated),
    speed(speed),
    angle(angle),
    targetsPlayer(targetsPlayer)
    distanceLeft(maxDistance),
    damage(damage),
    dir({cos(angle), sin(angle)})
{
  associated.AddComponent(new SpriteRenderer(associated, "Bullet.png"));
  associated.AddComponent(new Collider(associated));
}

void Bullet::Start()
{
}

void Bullet::Update(float dt)
{

  Vec2 displacement =  dir* speed * dt;
  associated.box.x += displacement.x;
  associated.rotation = angle + M_PI/2;
  associated.box.y += displacement.y;
  distanceLeft -= displacement.magnitude();
  if (distanceLeft <= 0) {
    associated.RequestDelete();
  }
}

void Bullet::NotifyCollision(GameObject& other)
{
  if(other.GetComponent<Zombie>() && !other.IsDead()) associated.RequestDelete();
}
void Bullet::Render(){}
int Bullet::GetDamage(){return damage;}

