#include "../include/Resources.h"
#include "../include/Game.h"

std::unordered_map<std::string, SDL_Texture*>  Resources::imageTable;
std::unordered_map<std::string, Mix_Music*>    Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*>    Resources::soundTable;
std::unordered_map<std::string, TTF_Font*>     Resources::fontTable;

SDL_Texture* Resources::GetImage(std::string file){
  auto it = imageTable.find(file);
  if(it != imageTable.end()){//if achou
    return it->second;}

  std::string path = "assets/img/" + file;
  SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), path.c_str());
  if(texture == nullptr)
  {
    std::cout << SDL_GetError()<<"\n";
    std::cout<<"Erro ao carregar sprite : "<< file<<"\n";
    return nullptr;
  }
  imageTable.insert({file,texture});
  return texture;

}
void Resources::ClearImages(){
  for(auto &it: imageTable){
    SDL_DestroyTexture(it.second);
  }
  imageTable.clear();
}

Mix_Music* Resources::GetMusic(std::string file){
  auto it = musicTable.find(file);
  if(it != musicTable.end()){
    return it->second;}
    std::string path = "assets/audio/" + file;
    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if(music == nullptr)
    {
    std::cout << SDL_GetError()<<"\n";
    std::cout<<"Erro ao carregar musica : "<< file<<"\n";
    return nullptr;
    }
    musicTable.insert({file,music});
  return music;
}
void Resources::ClearMusics(){
    for(auto &it: musicTable){
    Mix_FreeMusic(it.second);
  }
  musicTable.clear();
}

Mix_Chunk* Resources::GetSound(std::string file){
  auto it = soundTable.find(file);
  if(it != soundTable.end()){
    return it->second;}
  std::string path = "assets/audio/" + file;
  Mix_Chunk* chunk  = Mix_LoadWAV(path.c_str());
  if(chunk == nullptr)
  {
  std::cout << SDL_GetError()<<"\n";
  std::cout<<"Erro ao carregar sound : "<< file<<"\n";
  return nullptr;
  }
  soundTable.insert({file,chunk});

  return chunk;
}
void Resources::ClearSounds(){
  for(auto &chunk: soundTable){
    Mix_FreeChunk(chunk.second);
  }
  soundTable.clear();
}

TTF_Font* Resources::GetFont(std::string file, int size){
  if (size <= 0) {
    size = 1;
  }

  std::string key = file + "#" + std::to_string(size);
  auto it = fontTable.find(key);
  if(it != fontTable.end()){
    return it->second;
  }

  std::string path = "assets/font/" + file;
  TTF_Font* font = TTF_OpenFont(path.c_str(), size);
  if(font == nullptr)
  {
    std::cout << TTF_GetError() << "\n";
    std::cout << "Erro ao carregar fonte : " << file << "\n";
    return nullptr;
  }

  fontTable.insert({key, font});
  return font;
}

void Resources::ClearFonts(){
  for(auto &it: fontTable){
    TTF_CloseFont(it.second);
  }
  fontTable.clear();
}
