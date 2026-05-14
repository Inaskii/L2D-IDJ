#include "../../include/Collider.h"
#include "../../include/GameObject.h"

#define PI M_PI

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
	Vec2 center( box.GetCenter() );
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y) - center).rotated( associated.rotation/(180/PI) )
					+ center - Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y) - center).rotated( associated.rotation/(180/PI) )
					+ center - Camera::pos;
	points[1] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y + box.h) - center).rotated( associated.rotation/(180/PI) )
					+ center - Camera::pos;
	points[2] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x, box.y + box.h) - center).rotated( associated.rotation/(180/PI) )
					+ center - Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
}

void Collider::NotifyCollision(GameObject& other) {
}

void Collider::SetScale(Vec2 scale) {
  this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
  this->offset = offset;
}