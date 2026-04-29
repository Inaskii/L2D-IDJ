#include "../include/Sound.h"


Sound::Sound(){
    chunk = nullptr;
}
Sound::Sound(std::string file){
    Open(file);
}
Sound::~Sound(){
    if(chunk == nullptr) return;
    Stop();
    Mix_FreeChunk(chunk);
}
void Sound::Play (int times){
    Mix_PlayChannel(channel,chunk,times);
}
void Sound::Stop (){
    Mix_HaltChannel(channel);
}
void Sound::Open (std::string file){
    std::string path = "assets/" + file;
    chunk = Mix_LoadWAV(path.c_str());

}
bool Sound::IsOpen(){
    return chunk != nullptr;
}
