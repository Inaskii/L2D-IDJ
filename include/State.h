#pragma once
#include "includes.h"

class GameObject;
class Rect;

class State {
public:
  State();
  virtual ~State();

  virtual void Start() = 0;
  virtual void Pause() = 0;
  virtual void Resume() = 0;
  virtual void Update(float dt) = 0;
  virtual void Render() = 0;

  virtual std::weak_ptr<GameObject> AddObject(std::shared_ptr<GameObject> go);
  virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
  virtual bool IsTileBlocked(const Rect& box) const;

  bool PopRequested();
  bool QuitRequested();

  virtual void StartArray();
  virtual void UpdateArray(float dt);
  virtual void RenderArray();

  virtual void SpawnZombie(int x, int y) = 0;
  virtual void SpawnNPC(int x, int y) = 0;

protected:
  bool popRequested;
  bool quitRequested;
  bool started; 
  std::vector<std::shared_ptr<GameObject>> objectArray;
};