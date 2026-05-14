#pragma once
#include "Component.h"
#include "Timer.h"
#include "Vec2.h"

class AIController : public Component {
public:
  AIController(GameObject& associated);
  ~AIController();
  void Start();
  void Update(float dt);
  void Render();
  void NotifyCollision(GameObject& other);
private:
  enum AIState { MOVING, RESTING };
  static int npcCounter;
  AIState state;
  Timer restTimer;
  Vec2 destination;

  bool ShootAt(const Vec2& target);
};
