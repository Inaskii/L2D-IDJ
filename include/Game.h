#pragma once
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "includes.h"
#include "InputManager.h"
#include "State.h"

class State;
class Rect;
class Vec2;

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
