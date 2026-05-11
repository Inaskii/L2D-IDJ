#include "../include/Vec2.h"


Vec2::Vec2() {
	x = 0;
	y = 0;
}

Vec2::Vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vec2 Vec2::operator+(const Vec2& v) const {
	return Vec2(x + v.x, y + v.y);
}

Vec2 Vec2::operator-(const Vec2& v) const {
	return Vec2(x - v.x, y - v.y);
}

Vec2 Vec2::operator*(const float f) const {
	return Vec2(x * f, y * f);
}

Vec2 Vec2::operator/(const float f) const {
	if (f == 0) {
		return Vec2(0, 0);
	}
	return Vec2(x / f, y / f);
}

bool Vec2::operator==(const Vec2& v) const {
	return x == v.x && y == v.y;
}

bool Vec2::operator!=(const Vec2& v) const {
	return x != v.x || y != v.y;
}

Vec2& Vec2::operator=(const Vec2& v) {
	x = v.x;
	y = v.y;
	return *this;
}

Vec2& Vec2::operator=(std::initializer_list<float> list) {
    auto it = list.begin();

    if (list.size() >= 2) {
        x = *it++;
        y = *it;
    }

    return *this;
}//para poder fazer Vec2 vec = {0,0}

float Vec2::magnitude() const {
	return std::sqrt(x * x + y * y);
}

Vec2 Vec2::normalized() const {
	float mag = magnitude();
	if (mag == 0.0f) {
		return Vec2(0, 0);
	}
	return Vec2(x / mag, y / mag);
}

void Vec2::normalize() {
	*this = normalized();
}

Vec2 Vec2::rotated(float angle) const {
	float cosTheta = std::cos(angle);
	float sinTheta = std::sin(angle);

	return Vec2(
		x * cosTheta - y * sinTheta,
		y * cosTheta + x * sinTheta
	);
}

void Vec2::rotate(float angle) {
	*this = rotated(angle);
}


float Vec2::dist(const Vec2& a, const Vec2& b) {
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	return std::sqrt(dx * dx + dy * dy);
}
