#pragma once

#include "includes.h"
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include "Component.h"

class Text : public Component {
public:
  enum TextStyle {
    SOLID,
    SHADED,
    BLENDED
  };

  Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color);
  ~Text() override;

  void Start() override;
  void Update(float dt) override;
  void Render() override;
  void NotifyCollision(GameObject& other) override;

  void SetText(std::string text);
  void SetColor(SDL_Color color);
  void SetStyle(TextStyle style);
  void SetFontFile(std::string fontFile);
  void SetFontSize(int fontSize);
  void SetVisible(bool visible);

private:
  void RemakeTexture();

  TTF_Font* font;
  SDL_Texture* texture;
  std::string text;
  TextStyle style;
  std::string fontFile;
  int fontSize;
  SDL_Color color;
  bool visible;
};