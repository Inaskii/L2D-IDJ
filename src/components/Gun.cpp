#include "../include/Character.h"
#include "../include/Gun.h"
#include "../include/Bullet.h"


Gun::Gun(GameObject& associated, std::weak_ptr< GameObject>character):
Component(associated),
shotSound("Range.wav"),
reloadSound("PumpAction.mp3"),
state(ready),

angle(0){
  this->character = character;

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

void Gun::Update(float dt){
  auto player = character.lock();
  cdTimer.Update(dt);

  if (!player){
    associated.RequestDelete();
    return;
  }
  Vec2 center = player->box.GetCenter();
  Vec2 mousePos = {
    static_cast<float>(InputManager::GetInstance().GetMouseX()),
    static_cast<float>(InputManager::GetInstance().GetMouseY())
  };
  Vec2 aim = mousePos - center;
  bool flip = aim.x < 0;
  int offx = flip  ? -20:20;
  associated.box.x = center.x + offx - associated.box.w/2;
  associated.box.y = center.y + 10- associated.box.h/2;

  SpriteRenderer* playerRenderer = player->GetComponent<SpriteRenderer>();
  SpriteRenderer* gunRenderer = associated.GetComponent<SpriteRenderer>();
  if (!playerRenderer || !gunRenderer) {
    return;
  }
  associated.rotation = atan2(center.y - mousePos.y, center.x - mousePos.x) + M_PI;
  
  if (flip) {
    playerRenderer->FlipX(true);
    gunRenderer->FlipY(true);
  } else {
    // associated.rotation = -associated.rotation;
    playerRenderer->FlipX(false);
    gunRenderer->FlipY(false);
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
    if(cdTimer.Get() > 0.1){
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
 
void Gun::Shoot(Vec2 target){
  if(state != ready)return;
  auto player = character.lock();
  if (!player) {
    return;
  }
  state = shoot;

  float spread = 20;
  //adicionei multiplos tiros e spread para ser uma shotgun
  for(int i =0; i<5;i ++){

    Vec2 gunPos = associated.box.GetCenter();
    Vec2 dir = {target.x - gunPos.x, target.y - gunPos.y};
    dir.normalize();
    float angle = atan2(dir.y, dir.x) + (((std::rand() / (float)RAND_MAX) * spread - 10.0f) * M_PI / 180.0f);
    associated.rotation = angle;
    GameObject* bulletGO = new GameObject();
    bulletGO->box.x = gunPos.x;
    bulletGO->box.y = gunPos.y;
    bulletGO->AddComponent(new Bullet(*bulletGO, angle, 800.0f, 10, 600.0f));
    Game::GetInstance().GetState().AddObject(std::shared_ptr<GameObject>(bulletGO));
    shotSound.Play();
    cdTimer.Restart();
  }
}