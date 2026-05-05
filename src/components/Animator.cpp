#include "../../include/Animator.h"
#include "../../include/GameObject.h"
#include "../../include/SpriteRenderer.h"

Animator::Animator(GameObject& associated)  : Component(associated),
    frameEnd(0),
    frameStart(0),
    frameTime(0),
    timeElapsed(0),
    currentFrame(0)
{
  
}
void Animator::Update(float dt){
  if(frameTime == 0) return;

  timeElapsed += dt;
  bool change = false;
  while(timeElapsed > frameTime)
  {
    currentFrame++;
    change = true;
    timeElapsed-=frameTime;
  }
  if(currentFrame>frameEnd) currentFrame = frameStart;

  if(change){
    associated.GetComponent<SpriteRenderer>()->SetFrame(currentFrame);
  }
}
void Animator::Render(){

}
void Animator::SetAnimation(std::string name){
  auto it = animations.find(name);
  if(it == animations.end()) return;
  //std::cout << "start = " << frameStart<< " end ="  << frameEnd << ", current = " << currentFrame<<std::endl;
  frameStart = it->second.frameStart;
  frameEnd = it->second.frameEnd;
  frameTime = it->second.frameTime;
  currentFrame = frameStart;
  associated.GetComponent<SpriteRenderer>()->SetFrame(currentFrame);

}
void Animator::AddAnimation(std::string name, Animation anim){
  auto it = animations.find(name);
  if(it != animations.end()) return;

  animations.insert({name,anim});

}
