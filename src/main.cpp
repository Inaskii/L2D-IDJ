#include "../include/Game.h"

int main(int argc, char** argv)
{
  std::cout<<"Main iniciada\n";
  Game& game = Game::GetInstance();
  std::cout<<"Jogo iniciado\n";
  game.Run();
  return 0;
}