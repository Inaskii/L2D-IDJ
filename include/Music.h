#include "Game.h"

class Music
{

public:
  Music();
  Music(std::string file);
  ~Music();
  void Play (int time = -1);
  void wStop (int msToStop = 1500);
  void Open (std::string file);
  bool IsOpen();
  
private:
 Mix_Music* music;
};