#pragma once


class Vec2{
  public:
    float x;
    float y;

    Vec2();
    Vec2(float x, float y);
    // Operadores
    Vec2 operator+(const Vec2& v) const;
    Vec2 operator-(const Vec2& v) const;
    Vec2 operator*(const float f) const;
    Vec2 operator/(const float f) const;
    bool operator==(const Vec2& v) const;
    Vec2& operator=(const Vec2& v);

    float magnitude() const;
    Vec2 normalized() const;
    void normalize();
    Vec2 rotated(float angle) const;
    void rotate(float angle);

    static float atan2(float y,float x);
    static float dist(const Vec2& a, const Vec2& b);
    

};
