#include "../include/Music.h"
#include "../include/Resources.h"

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
  music = Resources::GetMusic(file);
}
bool Music::IsOpen(){
  return music != nullptr;
}
