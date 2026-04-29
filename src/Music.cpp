#include "../include/Music.h"


Music::Music(){
  music = nullptr;
}
Music::Music(std::string file){
  Open(file);
}
Music::~Music(){
  Stop();
  Mix_FreeMusic(music);
}
void Music::Play (int time){
  Mix_PlayMusic(music,time);
}
void Music::Stop (int msToStop){
  Mix_FadeOutMusic(msToStop);
}
void Music::Open (std::string file){
  std::string path = "assets/" + file;
  music = Mix_LoadMUS(path.c_str());

}
bool Music::IsOpen(){
  return music != nullptr;
}
