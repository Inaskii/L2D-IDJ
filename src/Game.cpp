#include <../include/Game.h>
#include <iostream>
Game* Game::instance= nullptr;

Game::Game(std::string title, int width, int height)
{
  int sdlInit = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
  if(sdlInit){
    std::cout <<"Deu erro\n";
    std::cout << SDL_GetError()<<"\n";
    return;
  }
  int imgInit = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
  int mixInit = Mix_Init(MIX_INIT_MP3);
  int mixOpenAudio = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
  int channels = Mix_AllocateChannels(8);
  SDL_Window *SDL_window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height, 0);
  SDL_Renderer *SDL_renderer = SDL_CreateRenderer(SDL_window, -1, SDL_RENDERER_ACCELERATED);
  if(SDL_window == nullptr or SDL_renderer == nullptr)
  {
    std::cout<< "Deu erro 2\n";
    std::cout << SDL_GetError()<<"\n";
  }

}


Game::~Game()
{
  Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  SDL_DestroyRenderer();
  SDL_DestroyWindow();

}