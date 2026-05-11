#pragma once
#include "includes.h"

class Vec2{
  public:
    float x;
    float y;

    Vec2();
    Vec2(float x, float y);
    
    Vec2 operator+(const Vec2& v) const;
    Vec2 operator-(const Vec2& v) const;
    Vec2 operator*(const float f) const;
    Vec2 operator/(const float f) const;
    bool operator==(const Vec2& v) const;
    bool operator!=(const Vec2& v) const;
    Vec2& operator=(const Vec2& v);
    Vec2& operator=(std::initializer_list<float> list);

    float magnitude() const;
    Vec2 normalized() const;
    void normalize();
    Vec2 rotated(float angle) const;
    void rotate(float angle);

    static float dist(const Vec2& a, const Vec2& b);

};
