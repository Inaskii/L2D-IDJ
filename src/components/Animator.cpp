#include "../../include/Animator.h"


Animator::Animator(GameObject& associated)  : Component(associated),
    frameEnd(0),
    frameStart(0),
    frameTime(0),
    timeElapsed(0),
    currentFrame(0),
{
  
}
void Animator::Update(float dt){

}
void Animator::Render(){

}
void Animator::SetAnimation(std::string name){
  
}
void Animator::AddAnimation(std::string name, Animation anim){
  animations.insert({name,anim});
}
