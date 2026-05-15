#include "../include/GameData.h"
#include "../include/EndState.h"
#include "../include/Camera.h"
#include "../include/Game.h"
#include "../include/GameObject.h"
#include "../include/InputManager.h"
#include "../include/TitleState.h"

EndState::EndState()
  : background(),
    backgroundMusic(),
    instructionText(nullptr)
{
}

EndState::~EndState()
{
}

void EndState::Start()
{
  Camera::Unfollow();
  Camera::pos = {0, 0};
  LoadAssets();
  StartArray();
}

void EndState::Pause()
{
}

void EndState::Resume()
{
  Camera::Unfollow();
  Camera::pos = {0, 0};
}

void EndState::Update(float dt)
{
  (void)dt;

  if (InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
    quitRequested = true;
  }

  if (InputManager::GetInstance().KeyPress(SPACE_KEY)) {
    popRequested = true;
    Game::GetInstance().Push(new TitleState());
  }

  UpdateArray(dt);
}

void EndState::Render()
{
  SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
  if (renderer == nullptr) {
    return;
  }

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  background.Render(0, 0, background.GetWidth(), background.GetHeigth());
  RenderArray();
  SDL_RenderPresent(renderer);
}

void EndState::SpawnZombie(int x, int y)
{
  (void)x;
  (void)y;
}

void EndState::SpawnNPC(int x, int y)
{
  (void)x;
  (void)y;
}

void EndState::LoadAssets()
{
  GameObject* instructionGO = new GameObject();
  instructionGO->box.x = 0;
  instructionGO->box.y = 0;

  if (GameData::playerVictory) {
    background.Open("Win.png");
    backgroundMusic.Open("endStateWin.ogg");
  } else {
    background.Open("Lose.png");
    backgroundMusic.Open("endStateLose.ogg");
  }

  background.cameraFollower = 1;
  backgroundMusic.Play(-1);

  instructionText = new Text(*instructionGO, "neodgm.ttf", 24, Text::BLENDED, "PRESS SPACE TO PLAY AGAIN - ESC TO QUIT", {255, 255, 255, 255});
  instructionGO->AddComponent(instructionText);
  instructionGO->box.x = 400 - instructionGO->box.w / 2;
  instructionGO->box.y = 540;

  AddObject(std::shared_ptr<GameObject>(instructionGO));
}