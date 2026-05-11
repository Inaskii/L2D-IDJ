#pragma once
#include "includes.h"
#include <algorithm>
#include "Rect.h"

class Component;
class Game;

class GameObject
{
public:
  GameObject();
  ~GameObject();
  void Update(float dt);
  void Start();
  void Render();
  bool IsDead();
  void RequestDelete();
  void AddComponent(Component* cpt);
  void RemoveComponent(Component* cpt);
  float rotation;//0 a 2pi
  template <typename T>
  T* GetComponent();
  Rect box;
private:
  std::vector <Component*> components;
  bool isDead;
};

template<typename T>
T* GameObject::GetComponent(){
	long unsigned int index;
	for(index=0;index<components.size();index++){
		T* component = dynamic_cast<T*>(components[index]);
		if(component != nullptr){
			return component;
		}
	}
	return nullptr;
}