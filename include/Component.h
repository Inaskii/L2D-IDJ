#pragma once
class GameObject;

class Component

{
public:
  Component(GameObject &associated);
  virtual ~Component();
  virtual void Update(float dt) = 0;
  virtual void Start() = 0;
  virtual void Render() = 0;
  virtual void NotifyCollision(GameObject& other) = 0;
protected:
  GameObject &associated;
};