#include "../include/Sprite.h"


Sprite::Sprite(){
  texture = nullptr;
}

Sprite::Sprite(std::string file,int frameCountW, int frameCountH){
  Open(file);
}
Sprite::~Sprite(){
  SDL_DestroyTexture(texture);
}
void Sprite::Open(std::string file){
  std::string path = "assets/" + file;
  texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), path.c_str());
  if(texture == nullptr)
  {
    std::cout << SDL_GetError()<<"\n";
    std::cout<<"Erro ao carregar sprite : "<< file<<"\n";
    return;
  }
  SDL_QueryTexture(texture, nullptr, nullptr, &width,&height);
}
void Sprite::SetClip(int x, int y, int w, int h){
  clipRect.x = x;
  clipRect.y = y;
  clipRect.w = w;
  clipRect.h = h;
}
void Sprite::Render(int x, int y, int w, int h){
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


