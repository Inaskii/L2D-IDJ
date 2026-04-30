#include "../include/Sound.h"
#include "../include/Resources.h"

Sound::Sound(){
    chunk = nullptr;
}
Sound::Sound(std::string file){
    Open(file);
}
Sound::~Sound(){
    return;
}
void Sound::Play (int times){
    Mix_PlayChannel(channel,chunk,times);
}
void Sound::Stop (){
    Mix_HaltChannel(channel);
}
void Sound::Open (std::string file){
    chunk = Resources::GetSound(file);
}
bool Sound::IsOpen(){
    return chunk != nullptr;
}
