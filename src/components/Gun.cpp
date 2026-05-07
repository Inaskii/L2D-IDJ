#include "../include/Gun.h"



Gun::Gun(GameObject& associated, std::weak_ptr< GameObject>character):
Component(associated),
shotSound(""),
reloadSound(""),
cooldownState(0),
angle(0){
  
}
void Gun::Update(float dt){
  
}
void Gun::Render(){

}
 
void Gun::Shoot(Vec2 target){

}
