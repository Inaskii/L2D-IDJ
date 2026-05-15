#include "../include/TitleState.h"
#include "../include/Camera.h"
#include "../include/Game.h"
#include "../include/GameObject.h"
#include "../include/InputManager.h"
#include "../include/Text.h"
#include "../include/Timer.h"
#include "../include/SpriteRenderer.h"
#include "../include/StageState.h"

TitleState::TitleState()
  : promptText(nullptr),
    blinkTimer(),
    promptVisible(true),
    blinkInterval(0.5f)
{
}

TitleState::~TitleState()
{
}

void TitleState::Start()
{
  Camera::Unfollow();
  Camera::pos = {0, 0};
  LoadAssets();
  StartArray();
  blinkTimer.Restart();
  promptVisible = true;
  if (promptText != nullptr) {
    promptText->SetVisible(true);
  }
}

void TitleState::Pause()
{
}

void TitleState::Resume()
{
  Camera::Unfollow();
  Camera::pos = {0, 0};
  blinkTimer.Restart();
  promptVisible = true;
  if (promptText != nullptr) {
    promptText->SetVisible(true);
  }
}

void TitleState::Update(float dt)
{
  blinkTimer.Update(dt);
  if (blinkTimer.Get() >= blinkInterval) {
    promptVisible = !promptVisible;
    if (promptText != nullptr) {
      promptText->SetVisible(promptVisible);
    }
    blinkTimer.Restart();
  }

  if (InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
    quitRequested = true;
  }

  if (InputManager::GetInstance().KeyPress(SPACE_KEY)) {
    Game::GetInstance().Push(new StageState());
  }

  UpdateArray(dt);
}

void TitleState::Render()
{
  SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
  if (renderer == nullptr) {
    return;
  }

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  RenderArray();
  SDL_RenderPresent(renderer);
}

void TitleState::SpawnZombie(int x, int y)
{
  (void)x;
  (void)y;
}

void TitleState::SpawnNPC(int x, int y)
{
  (void)x;
  (void)y;
}

void TitleState::LoadAssets()
{
  GameObject* titleGO = new GameObject();
  titleGO->box.x = -180;
  titleGO->box.y = -140;

  SpriteRenderer* titleRenderer = new SpriteRenderer(*titleGO, "Title.png");
  titleRenderer->SetCameraFollower(true);
  titleGO->AddComponent(titleRenderer);

  AddObject(std::shared_ptr<GameObject>(titleGO));

  GameObject* promptGO = new GameObject();
  promptGO->box.x = 0;
  promptGO->box.y = 0;

  promptText = new Text(*promptGO, "neodgm.ttf", 24, Text::BLENDED, "PRESS SPACE TO CONTINUE", {255, 255, 255, 255});
  promptGO->AddComponent(promptText);
  promptGO->box.x = 400 - promptGO->box.w / 2;
  promptGO->box.y = 520;

  AddObject(std::shared_ptr<GameObject>(promptGO));
}