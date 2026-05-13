#pragma once  
#include "Component.h"
#include "includes.h"
#include "Animation.h"

class Animator : public Component{
public:
  Animator(GameObject& associated);
  void Start();
  void Update(float dt);
  void Render();
  void NotifyCollision(GameObject& other);
  void SetAnimation(std::string name);
  void AddAnimation(std::string name, Animation anim);
private:
  std::unordered_map<std::string,Animation> animations;
  int frameStart;
  int frameEnd;
  float frameTime;
  int currentFrame;
  float timeElapsed;
};