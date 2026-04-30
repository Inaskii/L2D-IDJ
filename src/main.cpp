#include "../include/Game.h"
#include "../include/Resources.h"

int main(int argc, char** argv)
{
  std::cout<<"Main iniciada\n";
  Game& game = Game::GetInstance();
  std::cout<<"Jogo iniciado\n";
  game.Run();
  Resources::ClearImages();
  Resources::ClearMusics();
  Resources::ClearSounds();
  return 0;
}