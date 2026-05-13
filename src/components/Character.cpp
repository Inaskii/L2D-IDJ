#include "../include/Character.h"
#include "../include/Collider.h"
#include "../include/Zombie.h"

Character* Character::player = nullptr;

Character::Command::Command(CommandType type, float x, float y)
  : type(type),
    pos({x, y})
{
}


Character::Character (GameObject& associated, std::string sprite):
  Component(associated),
  hp(100),
  linearSpeed(12),
  speed({0,0}),
  taskQueue(),
  hit(false),
  dead(false),
  hitSound("Hit1.wav"),
  deathSound("Dead.wav")
{
  

    SpriteRenderer* spriteRenderer = new SpriteRenderer(associated,"Player.png",3,4);
    associated.AddComponent(spriteRenderer);

    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);

    

    Animator* animator = new Animator(associated);
    animator->AddAnimation("idle",Animation(9,9,0));
    animator->AddAnimation("walking",Animation(0,8,0.2f));
    animator->AddAnimation("dead",Animation(10,11,0));
    associated.AddComponent(animator);
}
Character::~Character (){
  Character::player = nullptr;
}
void Character::Start(){
  associated.GetComponent<Animator>()->SetAnimation("idle");
  
  auto ts = Game::GetInstance().GetState().GetObjectPtr(&associated);
  player = this;
  
  auto gunGO = std::make_shared<GameObject>();
  gunGO->AddComponent(new Gun(*gunGO,ts));
  gun = Game::GetInstance().GetState().AddObject(gunGO);

}
void Character::Update (float dt){
  if (dead) {
    deathTimer.Update(dt);
    if (deathTimer.Get() > 1.0f) {
      associated.RequestDelete();
    }
    return;
  }

  speed = {0,0};
  Animator* animator = associated.GetComponent<Animator>();
  while(taskQueue.size()){ 
    auto task = taskQueue.front();taskQueue.pop();
    if(task.type == Command::CommandType::shoot) {
      auto gunGO = gun.lock();
      if (gunGO) {
        auto gunComponent = gunGO->GetComponent<Gun>();
        if (gunComponent) {
          gunComponent->Shoot(task.pos);
        }
      }
    }

    if(task.type == Command::CommandType::move)
    {
      task.pos.y*=-1;
      speed = task.pos.normalized()*linearSpeed;
      animator->SetAnimation("walking");
    }
    
  }
  if(speed == Vec2{0,0}) animator->SetAnimation("idle"); 
  this->associated.box.x+=speed.x;
  this->associated.box.y+=speed.y;

  hitTimer.Update(dt);
  if (hit && hitTimer.Get() > 0.25f) {
    hit = false;
  }

}
void Character::Render (){}
void Character::NotifyCollision(GameObject& other){
  if (dead || hit) {
    return;
  }

  Zombie* zombie = other.GetComponent<Zombie>();
  if (zombie == nullptr) {
    return;
  }

  hp -= 10;
  hit = true;
  hitTimer.Restart();
  hitSound.Play(1);

  if (hp <= 0) {
    dead = true;
    Camera::Unfollow();
    deathTimer.Restart();
    deathSound.Play(1);
    auto animator = associated.GetComponent<Animator>();
    if (animator) {
      animator->SetAnimation("dead");
    }
  }
}
void Character::Issue (Command task){taskQueue.push(task); }
