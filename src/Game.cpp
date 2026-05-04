#include "../include/Game.h"

Game::Game(std::string title, int width, int height)
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

  window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if(window == nullptr or renderer == nullptr)
  {
    std::cout<< "Deu erro 2\n";
    std::cout << SDL_GetError()<<"\n";
  }
  std::cout <<"Chegamos aqui\n";
  state = new State();
  std::cout<<"Aqui\n";
}


Game::~Game()
{
  delete state;
  Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

State& Game::GetState(){return *state;}
float Game::GetDeltaTime(){return dt;}
SDL_Renderer* Game::GetRenderer(){return renderer;}

Game& Game::GetInstance()
{
  static Game instance("L2D-IDJ", 800, 600);
  return instance;
}

void Game::Run()
{
  std::cout<<"Jogo aberto\n";
  state->LoadAssets();
  while(!state->QuitRequested())
  {
    SDL_Delay(33);
    InputManager::GetInstance().Update();
    state->Update(33);
    state->Render();

  }
}
void Game::CalculateDeltaTime()
{
  //framestart -> valor antigo
  Uint32 currentFrame = SDL_GetTicks(); //atual
  dt = currentFrame - frameStart;
  frameStart = currentFrame;

}