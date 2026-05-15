#include "../include/Character.h"
#include "../include/Gun.h"
#include "../include/Bullet.h"


Gun::Gun(GameObject& associated, std::weak_ptr<GameObject> owner, bool targetsPlayer):
Component(associated),
shotSound("Range.wav"),
reloadSound("PumpAction.mp3"),
state(ready),
owner(owner),
targetsPlayer(targetsPlayer),
angle(0){

  SpriteRenderer* spriteRenderer = new SpriteRenderer(associated,"Gun.png",3,2);
  associated.AddComponent(spriteRenderer);

  Animator* animator = new Animator(associated);

  animator->AddAnimation("idle",Animation(0,2,0));
  animator->AddAnimation("reloading",Animation(3,5,0.1f));
  animator->SetAnimation("idle");
  associated.AddComponent(animator);  

  }

void Gun::Start(){
  Animator* animator = associated.GetComponent<Animator>();
  animator->SetAnimation("idle");
}

void Gun::Aim(Vec2 target){
  auto ownerGO = owner.lock();
  if (!ownerGO) {
    return;
  }

  Vec2 center = ownerGO->box.GetCenter();
  Vec2 aim = target - center;
  if (aim.magnitude() == 0) {
    return;
  }

  bool flip = aim.x < 0;
  int offx = flip ? -20 : 20;
  associated.box.x = center.x + offx - associated.box.w/2;
  associated.box.y = center.y + 10 - associated.box.h/2;
  associated.rotation = atan2(center.y - target.y, center.x - target.x) + M_PI;

  if (SpriteRenderer* gunRenderer = associated.GetComponent<SpriteRenderer>()) {
    gunRenderer->FlipY(flip);
  }
}

void Gun::Update(float dt){
  cdTimer.Update(dt);

  auto ownerGO = owner.lock();
  if (!ownerGO){
    associated.RequestDelete();
    return;
  }
  switch (state)
  {
  case ready:
    // if(cdTimer.Get() > 0.05f)
    // {
      // state = 
      // cdTimer.Restart();
    // }
    break;
  case shoot:
    if(cdTimer.Get() > 0.3){
      cdTimer.Restart();
      Animator* animator = associated.GetComponent<Animator>();
      animator->SetAnimation("reloading");
      state = reload;
      reloadSound.Play();
    }
    break;
  case reload:
    if(cdTimer.Get() > 0.3){
      state = pump;
      cdTimer.Restart();
      Animator* animator = associated.GetComponent<Animator>();
      animator->SetAnimation("idle");
    }
    break;
  case pump:
    if(cdTimer.Get() > 0.1){
      state = ready; 
    }
    break;


  default:
    break;

  }







}
void Gun::Render(){

}

void Gun::NotifyCollision(GameObject& other){

}
 
bool Gun::Shoot(Vec2 target){
  Aim(target);
  if(state != ready)return false;
  auto ownerGO = owner.lock();
  if (!ownerGO) {
    return false;
  }
  state = shoot;

  float spread = 25;
  //adicionei multiplos tiros e spread para ser uma shotgun
  for(int i =0; i<3;i ++){

    Vec2 gunPos = associated.box.GetCenter();
    Vec2 dir = {target.x - gunPos.x, target.y - gunPos.y};
    dir.normalize();
    float angle = atan2(dir.y, dir.x) + (((std::rand() / (float)RAND_MAX) * spread - spread / 2.0f) * M_PI / 180.0f);
    associated.rotation = angle;
    GameObject* bulletGO = new GameObject();
    bulletGO->box.x = gunPos.x;
    bulletGO->box.y = gunPos.y;
    bulletGO->AddComponent(new Bullet(*bulletGO, angle, 800.0f, 10, 600.0f,targetsPlayer));
    Game::GetInstance().GetCurrentState().AddObject(std::shared_ptr<GameObject>(bulletGO));
    shotSound.Play();
    cdTimer.Restart();
  }
  return true;
}