#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <State.h>
#include <Rect.h>
#include <Vec2.h>
#include <bits/stdc++.h>

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
