#pragma once
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "includes.h"
#include "Camera.h"

class Sprite
{
public:
  Sprite();
  Sprite(std::string file,int frameCountW = 1, int frameCountH = 1);
  ~Sprite();
  void Open(std::string file);
  void SetClip(int x, int y, int w, int h);
  void Render(int x, int y,int w, int h);
  int GetWidth();
  int GetHeigth();  
  bool isOpen();
  void setFrame(int frame);
  void setFrameCount(int frameCountW, int frameCountH);
  bool cameraFollower;
  private:
  SDL_Texture* texture;
  int width, height;
  SDL_Rect clipRect;
  int frameCountW, frameCountH;

};