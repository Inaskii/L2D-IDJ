#include "../../include/PlayerController.h"
#include "../../include/InputManager.h"
#include "../../include/Character.h"




PlayerController::PlayerController(GameObject& associated): 
Component(associated)
{

}
void PlayerController::Start(){

}
void PlayerController::Update(float dt){
  InputManager& inputManager = InputManager::GetInstance();
  auto player = associated.GetComponent<Character>();
  player->Issue(Character::Command(Character::Command::aim,inputManager.GetMouseX(),inputManager.GetMouseY()));
  Vec2 dir = {
    inputManager.IsKeyDown('d')-inputManager.IsKeyDown('a'),
    inputManager.IsKeyDown('w')-inputManager.IsKeyDown('s')
  };
  dir.normalize();
  if(dir != Vec2(0,0)) {
    // std::cout<<"Move "<< dir.x<<" " << dir.y << "\n";
    player->Issue(Character::Command(Character::Command::move, dir.x,dir.y));
  }
  
  if (inputManager.IsMouseDown(LEFT_MOUSE_BUTTON)) {
    player->Issue(Character::Command(Character::Command::shoot,inputManager.GetMouseX(),inputManager.GetMouseY()));
  }
}
  
void PlayerController::Render(){}
void PlayerController::NotifyCollision(GameObject& other){}