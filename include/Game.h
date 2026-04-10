#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <State.h>
#include <string>

class Game{
public:

  ~Game();
  void Run();
  SDL_Renderer *getRenderer();
  State& GetState (); 
  static Game& GetInstance ();
private:
  static Game  *instance;
  SDL_Window* window;
  SDL_Renderer* renderer;
  State *state;
  Game (std::string title,int width,int height);
  
  };
