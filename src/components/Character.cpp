#include "../include/Character.h"

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
  taskQueue()
{
  

    SpriteRenderer* spriteRenderer = new SpriteRenderer(associated,"Player.png",3,4);
    associated.AddComponent(spriteRenderer);

    

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

}
void Character::Render (){}
void Character::Issue (Command task){taskQueue.push(task); }
