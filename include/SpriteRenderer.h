#pragma once
#include "Component.h"
#include "Sprite.h"
#include "includes.h"

class SpriteRenderer : public Component {
public:
  SpriteRenderer(GameObject &associated);
  SpriteRenderer(GameObject &associated, std::string file, int frameCountW = 1, int frameCountH = 1);

  void Open(std::string file);
  void SetFrameCount(int frameCountW, int frameCountH);
  void Start();
  void Update(float dt) override;
  void Render() override;
  void SetFrame(int frame);
  void SetCameraFollower(bool b);
  void FlipX(bool flip);
  void FlipY(bool flip);
private:
  Sprite sprite;
  int frameCountW;
  int frameCountH;
};
