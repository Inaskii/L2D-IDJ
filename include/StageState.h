#pragma once

#include "State.h"
#include "Sprite.h"

class GameObject;
class TileMap;

class StageState : public State {
public:
  StageState();
  ~StageState() override;

  void LoadAssets();
  void Start() override;
  void Pause() override;
  void Resume() override;
  void Update(float dt) override;
  void Render() override;
  void SpawnZombie(int x, int y) override;
  void SpawnNPC(int x, int y) override;
  bool IsTileBlocked(const Rect& box) const override;

  Sprite sprite;

private:
  void TriggerEnd(bool playerVictory);

  TileMap* tileMap;
  std::weak_ptr<GameObject> waveSpawner;
  bool ending;
};