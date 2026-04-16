#include "../include/GameObject.h"



GameObject::GameObject(){
  isDead=  false;
}
GameObject::~GameObject(){
  for(Component *Component:components)
  {
    Component->~Component();
  }
}
void GameObject::Update(float dt){
  for(Component *Component:components)
  {
    Component->Update(dt);
  }
}
void GameObject::Render(){
  for(Component *Component:components)
  {
    Component->Render();
  }

}
bool GameObject::IsDead(){
  return isDead;
}
void GameObject::RequestDelete(){
  isDead = true;
}
void GameObject::AddComponent(Component* cpt){
  components.push_back(cpt);
}
void GameObject::RemoveComponent(Component* cpt){
  // o(n) tentar otimizar depois
  auto it = std::find(components.begin(), components.end(), cpt);
  if (it != components.end()) {
    components.erase(it);
  }
}
    
