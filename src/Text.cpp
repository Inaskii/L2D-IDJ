#include "../include/Text.h"
#include "../include/Camera.h"
#include "../include/Game.h"
#include "../include/GameObject.h"
#include "../include/Resources.h"

Text::Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color)
  : Component(associated),
    font(nullptr),
    texture(nullptr),
    text(text),
    style(style),
    fontFile(fontFile),
    fontSize(fontSize),
    color(color),
    visible(true)
{
  RemakeTexture();
}

Text::~Text()
{
  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
    texture = nullptr;
  }
}

void Text::Start()
{
}

void Text::Update(float dt)
{
  (void)dt;
}

void Text::Render()
{
  if (!visible || texture == nullptr) {
    return;
  }

  SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
  if (renderer == nullptr) {
    return;
  }

  SDL_Rect clipRect = {0, 0, static_cast<int>(associated.box.w), static_cast<int>(associated.box.h)};
  SDL_Rect destRect = {
    static_cast<int>(associated.box.x - Camera::pos.x),
    static_cast<int>(associated.box.y - Camera::pos.y),
    static_cast<int>(associated.box.w),
    static_cast<int>(associated.box.h)
  };

  SDL_RenderCopyEx(renderer, texture, &clipRect, &destRect, 0, nullptr, SDL_FLIP_NONE);
}

void Text::NotifyCollision(GameObject& other)
{
  (void)other;
}

void Text::SetText(std::string text)
{
  this->text = text;
  RemakeTexture();
}

void Text::SetColor(SDL_Color color)
{
  this->color = color;
  RemakeTexture();
}

void Text::SetStyle(TextStyle style)
{
  this->style = style;
  RemakeTexture();
}

void Text::SetFontFile(std::string fontFile)
{
  this->fontFile = fontFile;
  RemakeTexture();
}

void Text::SetFontSize(int fontSize)
{
  this->fontSize = fontSize;
  RemakeTexture();
}

void Text::SetVisible(bool visible)
{
  this->visible = visible;
}

void Text::RemakeTexture()
{
  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
    texture = nullptr;
  }

  if (fontSize <= 0) {
    fontSize = 1;
  }

  font = Resources::GetFont(fontFile, fontSize);
  if (font == nullptr) {
    return;
  }

  SDL_Surface* surface = nullptr;
  SDL_Color black = {0, 0, 0, 255};
  if (style == SOLID) {
    surface = TTF_RenderText_Solid(font, text.c_str(), color);
  } else if (style == SHADED) {
    surface = TTF_RenderText_Shaded(font, text.c_str(), color, black);
  } else {
    surface = TTF_RenderText_Blended(font, text.c_str(), color);
  }

  if (surface == nullptr) {
    std::cout << TTF_GetError() << "\n";
    return;
  }

  SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
  if (renderer == nullptr) {
    SDL_FreeSurface(surface);
    return;
  }

  texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture != nullptr) {
    associated.box.w = surface->w;
    associated.box.h = surface->h;
  } else {
    std::cout << SDL_GetError() << "\n";
  }

  SDL_FreeSurface(surface);
}