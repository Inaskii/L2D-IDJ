#include "../../include/Collider.h"
#include "../../include/GameObject.h"

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset)
  : Component(associated),
    box(),
    scale(scale),
    offset(offset) {
}

void Collider::Start() {
  box = associated.box;
  box.w *= scale.x;
  box.h *= scale.y;
  box.x = associated.box.GetCenter().x + offset.rotated(associated.rotation).x - box.w / 2.0f;
  box.y = associated.box.GetCenter().y + offset.rotated(associated.rotation).y - box.h / 2.0f;
}

void Collider::Update(float dt) {
  box = associated.box;
  box.w *= scale.x;
  box.h *= scale.y;
  box.x = associated.box.GetCenter().x + offset.rotated(associated.rotation).x - box.w / 2.0f;
  box.y = associated.box.GetCenter().y + offset.rotated(associated.rotation).y - box.h / 2.0f;
}

void Collider::Render() {
}

void Collider::NotifyCollision(GameObject& other) {
}

void Collider::SetScale(Vec2 scale) {
  this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
  this->offset = offset;
}