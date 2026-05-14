#include "../include/GameObject.h"
#include "../include/Component.h"

GameObject::GameObject(){
  isDead=  false;
  rotation = 0.0f;
}
GameObject::~GameObject(){
  for(Component *Component:components)
  {
    delete Component;
  }
}
void GameObject::Die(){isDead=1;}
void GameObject::Start()
{
  const size_t componentCount = components.size();
  for (size_t i = 0; i < componentCount; i++)
  {
    components[i]->Start();
  }     
}

void GameObject::Update(float dt){
  for(Component *Component:components)
  {
    Component->Update(dt);
  }     
}
void GameObject::Render(){
  for(Component *Component:components){
    Component->Render();
  }

}
void GameObject::NotifyCollision(GameObject& other){
  for (size_t i = 0; i < components.size(); i++) {
    components[i]->NotifyCollision(other);
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
  cpt->Start();
}
void GameObject::RemoveComponent(Component* cpt){
  // o(n) tentar otimizar depois
  auto it = std::find(components.begin(), components.end(), cpt);
  if (it != components.end()) {
    delete *it;
    components.erase(it);
  }
}
    
