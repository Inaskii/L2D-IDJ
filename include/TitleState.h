#pragma once

#include "State.h"
#include "Text.h"
#include "Timer.h"

class TitleState : public State {
public:
  TitleState();
  ~TitleState() override;

  void LoadAssets();
  void Start() override;
  void Pause() override;
  void Resume() override;
  void Update(float dt) override;
  void Render() override;
  void SpawnZombie(int x, int y) override;
  void SpawnNPC(int x, int y) override;

private:
  Text* promptText;
  Timer blinkTimer;
  bool promptVisible;
  float blinkInterval;
};