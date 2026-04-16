#pragma once
#include "Game.h"

class Sprite
{
public:
  Sprite();
  Sprite(std::string file);
  ~Sprite();
  void Open(std::string file);
  void SetClip(int x, int y, int w, int h);
  void Render(int x, int y);
  int GetWidth();
  int GetHeigth();
  bool isOpen();
private:
  SDL_Texture* texture;
  int width, height;
  SDL_Rect clipRect;

};