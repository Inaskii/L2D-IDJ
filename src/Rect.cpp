#include "../include/Rect.h"

Rect::Rect()
{
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}

Rect::Rect(float x, float y, float w, float h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

Rect Rect::operator+(const Vec2& v) const
{
    return Rect(x + v.x, y + v.y, w, h);
}

Rect Rect::operator-(const Vec2& v) const
{
    return Rect(x - v.x, y - v.y, w, h);
}

Rect& Rect::operator=(const Rect& r)
{
    x = r.x;
    y = r.y;
    w = r.w;
    h = r.h;
    return *this;
}

Rect& Rect::operator+=(const Vec2& v)
{
    x += v.x;
    y += v.y;
    return *this;
}

Rect& Rect::operator-=(const Vec2& v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

Vec2 Rect::GetCenter() const
{
    return Vec2(x + w / 2.0f, y + h / 2.0f);
}

bool Rect::Contains(const Vec2& point) const
{
    return Contains(point.x, point.y);
}

bool Rect::Contains(float pointX, float pointY) const
{
    return pointX >= x && pointX <= x + w && pointY >= y && pointY <= y + h;
}

float Rect::DistanceBetweenCenters(const Rect& a, const Rect& b)
{
    return Vec2::dist(a.GetCenter(), b.GetCenter());
}

Rect::~Rect()
{
}