#include "../include/Sound.h"
#include "../include/Resources.h"

Sound::Sound(){
    chunk = nullptr;
    channel = -1;
}
Sound::Sound(std::string file){
    chunk = nullptr;
    channel = -1;
    Open(file);
}
Sound::~Sound(){
    return;
}
void Sound::Play (int times){
    if(chunk == nullptr) return;
    Mix_PlayChannel(channel,chunk,times);
}
void Sound::Stop (){
    if(channel < 0) return;
    Mix_HaltChannel(channel);
}
void Sound::Open (std::string file){
    chunk = Resources::GetSound(file);
}
bool Sound::IsOpen(){
    return chunk != nullptr;
}
