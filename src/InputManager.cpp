#include "../include/InputManager.h"
#define INCLUDE_SDL
#include "../include/SDL_include.h"

InputManager& InputManager::GetInstance() {
  static InputManager instance;
  return instance;
}


void InputManager::Update()
{
  SDL_Event event;
  updateCounter++;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        quitRequested = true;
        break;
      case SDL_MOUSEBUTTONDOWN: {
        int button = event.button.button;
        if (button >= 0 && button < 6) {
          mouseState[button] = true;
          mouseUpdate[button] = updateCounter;
        }
        break;}
      case SDL_MOUSEBUTTONUP: {
        int button = event.button.button;
        if (button >= 0 && button < 6) {
          mouseState[button] = false;
          mouseUpdate[button] = updateCounter;
        }
      } break;
      case SDL_MOUSEMOTION:
        mouseX = event.motion.x;
        mouseY = event.motion.y;
        break;
      case SDL_KEYDOWN: {
        if (event.key.repeat == 0) {
          int key = event.key.keysym.sym;
          keyState[key] = true;
          keyUpdate[key] = updateCounter;
        }
      } break;
      case SDL_KEYUP: {
        int key = event.key.keysym.sym;
        keyState[key] = false;
        keyUpdate[key] = updateCounter;
      } break;
      default:
        break;
      }
  }
}
bool InputManager::KeyPress(int key){
  if(keyState[key] && keyUpdate[key] == updateCounter) return true;}
bool InputManager::KeyRelease(int key){
  if(!keyState[key] && keyUpdate[key] == updateCounter) return true;}
bool InputManager::IsKeyDown(int key){
  if(keyState[key]) return true;}
bool InputManager::MousePress(int button){
  if(mouseState[button] && mouseUpdate[button] == updateCounter) return true;}
bool InputManager::MouseRelease(int button){
  if(!mouseState[button] && mouseState[button] == updateCounter) return true;}
bool InputManager::IsMouseDown(int button){
  if(mouseState[button]) return true;}

int InputManager::GetMouseX(){return mouseX;}
int InputManager::GetMouseY(){return mouseY;}
bool InputManager::QuitRequested(){return quitRequested;}

InputManager::InputManager(){
  quitRequested = false;
  updateCounter = 0;
  mouseX = 0;
  mouseY = 0;

  for (int i = 0; i < 6; ++i) {
    mouseState[i] = false;
    mouseUpdate[i] = 0;
  }
}
InputManager::~InputManager(){}