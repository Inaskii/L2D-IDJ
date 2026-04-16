#pragma once
#include "Vec2.h"

class Rect{
public:
  float x, y, w, h;

  Rect();
  Rect(float x,float y,float w,float h);

  Rect operator+(const Vec2& v) const;
  Rect operator-(const Vec2& v) const;
  Rect& operator=(const Rect& r);
  Rect& operator+=(const Vec2& v);
  Rect& operator-=(const Vec2& v);

  Vec2 GetCenter() const;
  bool Contains(const Vec2& point) const;
  bool Contains(float pointX, float pointY) const;

  static float DistanceBetweenCenters(const Rect& a, const Rect& b);

  ~Rect();
};