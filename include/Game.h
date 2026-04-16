#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>

class State;

class Game{
public:

  ~Game();
  void Run();
  SDL_Renderer *GetRenderer();
  State& GetState (); 
  static Game& GetInstance ();
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  State* state;
  Game (std::string title,int width,int height);
  
  };
