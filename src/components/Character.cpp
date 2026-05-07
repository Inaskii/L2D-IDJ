#include "../include/Character.h"
#include "../include/SpriteRenderer.h"
#include "../include/Animator.h"

Character::Command::Command(CommandType type, float x, float y){pos = {x,y};}

Character::Character (GameObject& associated, std::string sprite):
  Component(associated),
  hp(100),
  linearSpeed(0),
  speed({0,0}),
  taskQueue()
{
  

    SpriteRenderer* spriteRenderer = new SpriteRenderer(associated,"Player.png",3,4);
    associated.AddComponent(spriteRenderer);


    Animator* animator = new Animator(associated);
    animator->AddAnimation("idle",Animation(9,9,0));
    animator->AddAnimation("walking",Animation(0,8,0.06f));
    animator->AddAnimation("dead",Animation(10,11,0));
    animator->SetAnimation("idle");
    associated.AddComponent(animator);
}
Character::~Character (){}
void Character::Start(){}
void Character::Update (float dt){}
void Character::Render (){}
void Character::Issue (Command task){}

  
// static Character* player;
//   std::weak_ptr< GameObject > gun;
//   std::queue<Command> taskQueue;
//   Vec2 speed;
//   float linearSpeed;
//   int hp;
//   Timer deathTimer();


