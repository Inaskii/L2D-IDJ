#include "Character.h"
#include "Sound.h"
class Gun: Component{
public:
  Gun(GameObject& associated, std::weak_ptr< GameObject>character);
  void Update(float dt);
  void Render();
  void Shoot(Vec2 target);
private:
  Sound shotSound;
  Sound reloadSound;
  int cooldownState;
  Timer cdTimer;
  std::weak_ptr<GameObject> character;
  float angle;

};