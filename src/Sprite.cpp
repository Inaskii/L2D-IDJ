#include "../include/Sprite.h"
#include "../include/Game.h"
#include "../include/Resources.h"


Sprite::Sprite(){
  texture = nullptr;
  flip = SDL_FLIP_NONE;
}
  Sprite::Sprite(std::string file,int frameCountW, int frameCountH):
  cameraFollower(false){
  flip = SDL_FLIP_NONE;
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
void Sprite::Render(int x, int y, int w, int h, float angle){
  if(!cameraFollower) {x-=Camera::pos.x, y-=Camera::pos.y;}

  SDL_Rect temp;
  temp.x = x;
  temp.y = y;
  temp.w = w;
  temp.h = h;
  SDL_Point center = {temp.w / 2, temp.h / 2};
  SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &temp, angle, &center, flip);

}
void Sprite::SetFlip(SDL_RendererFlip newFlip){
  flip = newFlip;
}
void Sprite::FlipX(bool flipX){
  if (flipX) {
    flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_HORIZONTAL);
  } else {
    flip = static_cast<SDL_RendererFlip>(flip & ~SDL_FLIP_HORIZONTAL);
  }
}
void Sprite::FlipY(bool flipY){
  if (flipY) {
    flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_VERTICAL);
  } else {
    flip = static_cast<SDL_RendererFlip>(flip & ~SDL_FLIP_VERTICAL);
  }
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


