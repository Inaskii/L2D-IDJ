#include "../include/Game.h"
#include "../include/Resources.h"


Game::Game(std::string title, int width, int height)
  : window(nullptr),
    renderer(nullptr),
    storedState(nullptr),
    frameStart(0),
    dt(0.0f)
{

  int sdlInit = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
  if(sdlInit){
    std::cout <<"Deu erro\n";
    std::cout << SDL_GetError()<<"\n";
    return;
  }

  std::cout<<"SDLINIT aberto\n";
  int imgInit = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
  int mixInit = Mix_Init(MIX_INIT_MP3);
  int mixOpenAudio = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
  int channels = Mix_AllocateChannels(8);
  if (TTF_Init() != 0) {
    std::cout << TTF_GetError() << "\n";
  }

  window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if(window == nullptr or renderer == nullptr)
  {
    std::cout<< "Deu erro 2\n";
    std::cout << SDL_GetError()<<"\n";
  }

  frameStart = SDL_GetTicks();
}


Game::~Game()
{
  if (storedState != nullptr) {
    delete storedState;
    storedState = nullptr;
  }

  while (!stateStack.empty()) {
    stateStack.pop();
  }

  Resources::ClearImages();
  Resources::ClearMusics();
  Resources::ClearSounds();
  Resources::ClearFonts();

  Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  TTF_Quit();
  if (renderer != nullptr) {
    SDL_DestroyRenderer(renderer);
  }
  if (window != nullptr) {
    SDL_DestroyWindow(window);
  }
  SDL_Quit();
}

State& Game::GetCurrentState(){return *stateStack.top();}
State& Game::GetState(){return GetCurrentState();}
GameData& Game::GetGameData(){return gameData;}
float Game::GetDeltaTime(){return dt;}
SDL_Renderer* Game::GetRenderer(){return renderer;}

void Game::Push(State* state)
{
  if (storedState != nullptr) {
    delete storedState;
  }
  storedState = state;
}

Game& Game::GetInstance()
{
  static Game instance("L2D-IDJ", 800, 600);
  return instance;
}

void Game::Run()
{
  std::cout<<"Jogo aberto\n";
  auto processPendingStateChanges = [this]() {
    if (!stateStack.empty() && stateStack.top()->PopRequested()) {
      stateStack.pop();
      if (!stateStack.empty()) {
        stateStack.top()->Resume();
      }
    }

    if (storedState != nullptr) {
      if (!stateStack.empty()) {
        stateStack.top()->Pause();
      }

      stateStack.push(std::unique_ptr<State>(storedState));
      storedState = nullptr;
      stateStack.top()->Start();
    }
  };

  processPendingStateChanges();
  if (stateStack.empty()) {
    return;
  }

  while(!stateStack.empty() && !stateStack.top()->QuitRequested())
  {
    processPendingStateChanges();
    if (stateStack.empty() || stateStack.top()->QuitRequested()) {
      continue;
    }

    CalculateDeltaTime();

    InputManager::GetInstance().Update();
    stateStack.top()->Update(dt);
    stateStack.top()->Render();

    SDL_Delay(33);
  }
}

void Game::CalculateDeltaTime()
{
  Uint32 currentFrame = SDL_GetTicks();
  dt = (currentFrame - frameStart) / 1000.0f; 
  frameStart = currentFrame;
}