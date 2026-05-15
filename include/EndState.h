#pragma once

#include "State.h"
#include "Sprite.h"
#include "Music.h"
#include "Text.h"

class EndState : public State {
public:
  EndState();
  ~EndState() override;

  void LoadAssets();
  void Start() override;
  void Pause() override;
  void Resume() override;
  void Update(float dt) override;
  void Render() override;
  void SpawnZombie(int x, int y) override;
  void SpawnNPC(int x, int y) override;

private:
  Sprite background;
  Music backgroundMusic;
  Text* instructionText;
};