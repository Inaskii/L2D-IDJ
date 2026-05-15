#include "../include/Game.h"
#include "../include/TitleState.h"

int main(int argc, char** argv)
{
  std::cout<<"Main iniciada\n";
  Game& game = Game::GetInstance();
  std::cout<<"Jogo iniciado\n";
  game.Push(new TitleState());
  game.Run();
  return 0;
}