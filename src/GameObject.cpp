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

void GameObject::Start()
{
  for(Component *Component:components)
  {
    Component->Start();
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
    
