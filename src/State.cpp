#include "../include/State.h"
#include "../include/Sprite.h"
#include "../include/Music.h"
#include "../include/GameObject.h"
#include "../include/Game.h"
#define INCLUDE_SDL
#include "../include/SDL_include.h"

State::State()
  : sprite(),
    music(),
    quitRequested(false)
{
}
State::~State()
{
  objectArray.clear();
}
void State::LoadAssets()
{
  sprite.Open("image.png");
  if (sprite.isOpen()) {
    sprite.SetClip(0, 0, sprite.GetWidth(), sprite.GetHeigth());
  }

  music.Open("music.wav");
  if (music.IsOpen()) {
    music.Play();
  }
}


bool State::QuitRequested()
{
  return quitRequested;
}
void State::Update(float dt)
{
  if(SDL_QuitRequested())
  {
    quitRequested = true;
  }
  for (const std::unique_ptr<GameObject>& gameObject : objectArray)
  {
    gameObject->Update(dt);
  }
}
void State::Render()
{
  SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
  if (renderer == nullptr) {
    return;
  }

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  sprite.Render(0, 0, sprite.GetWidth(), sprite.GetHeigth());
  SDL_RenderPresent(renderer);
}
