
#include "Component.h"
#include "Vec2.h"
#include "includes.h"
#include "Timer.h"
#include "SpriteRenderer.h"
#include "Game.h"
#include "Animator.h"
#include "Gun.h"
#include "Sound.h"

class Character: public Component{
public:
  class Command {
    public:
      enum CommandType { move, shoot };
      Command(CommandType type, float x, float y);
      CommandType type;
      Vec2 pos;
  };

  Character (GameObject& associated, std::string sprite);
  ~Character ();
  void Start();
  void Update (float dt);
  void Render ();
  void NotifyCollision(GameObject& other);
  void Issue (Command task);
  static Character* player;
  
private:
  std::weak_ptr< GameObject > gun;
  std::queue<Command> taskQueue;
  Vec2 speed;
  float linearSpeed;
  int hp;
  bool hit;
  bool dead;
  Sound hitSound;
  Sound deathSound;
  Timer hitTimer;
  Timer deathTimer;
};


