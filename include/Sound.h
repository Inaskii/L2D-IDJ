#pragma once
#define INCLUDE_SDL_MIXER
#include "includes.h"
#include "SDL_include.h"

class Sound {
public:
    Sound();
    Sound(std::string file);
    ~Sound();
    void Play(int times = 1);
    void Stop();
    void Open (std::string file);
    bool IsOpen();

private:
    Mix_Chunk* chunk;
    int channel;
};
