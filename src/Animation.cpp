#include "../include/Animation.h"


Animation::Animation(int frameStart,int frameEnd, float frameTime){
  this->frameEnd = frameEnd;
  this->frameTime = frameTime;
  this->frameStart = frameStart;
}