#pragma once
#include <iostream>
#include "MyMath.h"


class Vector2 {
public:
	float x;
	float y;

public:
	Vector2()
		: x(0)
		, y(0) {
	}

	Vector2(const float _x, const float _y) {
		x = _x;
		y = _y;
	}

	Vector2 operator+() const {
		return *this;
	}

	Vector2 operator-() const {
		return Vector2(-x, -y);
	}

	Vector2 operator+(const Vector2& _vec) const {
		return Vector2(x + _vec.x, y + _vec.y);
	}

	Vector2 operator-(const Vector2& _vec) const {
		return Vector2(x - _vec.x, y - _vec.y);
	}

	Vector2 operator*(const float _val) const {
		return Vector2(x * _val, y * _val);
	}

	Vector2 operator/(const float _val) const {
		if (FloatEqual(_val, 0))
			return Vector2(0, 0);
		return Vector2(x / _val, y / _val);
	}

	Vector2& operator+=(const Vector2& _vec) {
		x += _vec.x;
		y += _vec.y;
		return *this;
	}

	Vector2& operator-=(const Vector2& _vec) {
		x -= _vec.x;
		y -= _vec.y;
		return *this;
	}

	Vector2& operator*=(const float _val) {
		x *= _val;
		y *= _val;
		return *this;
	}

	Vector2& operator/=(const float _val) {
		if (FloatEqual(_val, 0)) {
			x = 0;
			y = 0;
		}
		else {
			x /= _val;
			y /= _val;
		}
		return *this;
	}

	bool operator==(const Vector2& _vec) const {
		return FloatEqual(x, _vec.x) && FloatEqual(y, _vec.y);
	}

	bool operator!=(const Vector2& _vec) const {
		return !(FloatEqual(x, _vec.x) && FloatEqual(y, _vec.y));
	}

	friend std::istream& operator>>(std::istream& _is, Vector2& _vec) {
		_is >> _vec.x >> _vec.y;
		return _is;
	}

	friend std::ostream& operator<<(std::ostream& _os, const Vector2& _vec) {
		_os << "x = " << _vec.x << ", y = " << _vec.y;
		return _os;
	}

	Vector2(const Vector2& _vec) {
		*this = _vec;
	}

	Vector2& operator=(const Vector2& _vec) {
		x = _vec.x;
		y = _vec.y;
		return *this;
	}

	static float atan2fbyVec2(const Vector2& _from, const Vector2& _target);
	static float length(const Vector2& _vec);
	static float lengthSquare(const Vector2& _vec);
	static float distance(const Vector2& _pos1, const Vector2& _pos2);
	static float distanceSquare(const Vector2& _pos1, const Vector2& _pos2);
	static Vector2 normalize(const Vector2& _vec);
	static float dot(const Vector2& _vec1, const Vector2& _vec2);
	static float cross(const Vector2& _vec1, const Vector2& _vec2);
	static Vector2 createWithAngleNorm(const float _angle, const float _norm);
	static float vector2ToAngle(const Vector2& _vec);
	static Vector2 clamp(const Vector2& _vec, const Vector2& _min, const Vector2& _max);
	static Vector2 rotate(const Vector2& _vec, const float _rad, const Vector2& _center = Vector2(0,0));
};
