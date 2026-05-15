#pragma once
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include "includes.h"
#include "InputManager.h"
#include "GameData.h"
#include "State.h"
#include <stack>

class State;
class Rect;
class Vec2;

class Game{
public:

  ~Game();
  void Run();
  SDL_Renderer *GetRenderer();
  State& GetCurrentState();
  State& GetState();
  GameData& GetGameData();
  void Push(State* state);
  static Game& GetInstance ();
  float GetDeltaTime();

private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  State* storedState;
  GameData gameData;
  std::stack<std::unique_ptr<State>> stateStack;
  Game (std::string title,int width,int height);
  int frameStart;
  float dt;
  void CalculateDeltaTime();
  };
