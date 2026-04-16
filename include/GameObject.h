#pragma once
#include "Component.h"
#include "Game.h"

class GameObject
{
public:
  GameObject();
  ~GameObject();
  void Update(float dt);
  void Render();
  bool IsDead();
  void RequestDelete();
  void AddComponent(Component* cpt);
  void RemoveComponent(Component* cpt);
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
		T* component = dynamic_cast<T*>(components[index].get());
		if(component != nullptr){
			return component;
		}
	}
	return nullptr;
}