#include "../include/Camera.h"
#include "../include/includes.h"
Vec2 Camera::pos = {0,0};
Vec2 Camera::speed = {0,0};
GameObject* Camera::focus = nullptr;


void Camera::Follow(GameObject* newFocus) {focus = newFocus;}
void Camera::Unfollow() {focus = nullptr;}
void Camera::Update(float dt)
{
  if(focus != nullptr){
    pos.x = focus->box.x+focus->box.w/2;
    pos.y = focus->box.y+focus->box.h/2;
  }
  else{
    InputManager& input = InputManager::GetInstance();    
    //Usando WASD
    speed = {0,0};
    if(input.IsKeyDown('w')) speed.y--;//por algum motivo y é invertido
    if(input.IsKeyDown('s')) speed.y++;
    if(input.IsKeyDown('a')) speed.x--;
    if(input.IsKeyDown('d')) speed.x++;
    pos = pos + (speed*dt*1000);

    //std::cout<<pos.x<<" "<<pos.y<<std::endl;
  }
}
 