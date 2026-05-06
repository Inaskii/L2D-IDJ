#include "../include/Sprite.h"
#include "../include/Game.h"
#include "../include/Resources.h"


Sprite::Sprite(){
  texture = nullptr;
}
  Sprite::Sprite(std::string file,int frameCountW, int frameCountH):
  cameraFollower(false){
  Open(file);
}
Sprite::~Sprite(){
  return;
}
void Sprite::Open(std::string file){
  texture = Resources::GetImage(file);
  if(!isOpen()){
    std::cout << "Erro ao abrir " << file << std::endl;
    width = 0;
    height = 0;
    clipRect.x = clipRect.y = clipRect.w = clipRect.h = 0;
    return;
  }
  SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
  SetClip(0, 0, width, height);
}
void Sprite::SetClip(int x, int y, int w, int h){
  clipRect.x = x;
  clipRect.y = y;
  clipRect.w = w;
  clipRect.h = h;
}
void Sprite::Render(int x, int y, int w, int h){
  if(!cameraFollower) {x-=Camera::pos.x, y-=Camera::pos.y;}

  SDL_Rect temp;
  temp.x = x;
  temp.y = y;
  temp.w = clipRect.w;
  temp.h = clipRect.h;
  SDL_RenderCopy(Game::GetInstance().GetRenderer(),texture,&clipRect,&temp);

}
int Sprite::GetWidth(){
  return width;
}
int Sprite::GetHeigth(){
  return height;
}
bool Sprite::isOpen(){
  return texture != nullptr;
}
void Sprite::setFrame(int frame){
  SetClip(0,0,width,height);
}
void Sprite::setFrameCount(int frameCountW, int frameCountH){
  this->frameCountW = frameCountW;
  this->frameCountH = frameCountH;
}


