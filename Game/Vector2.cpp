#include "Vector2.h"
#include <iostream>

using namespace std;


float Vector2::length(const Vector2& _vec) {
	return sqrtf(lengthSquare(_vec));
}

float Vector2::lengthSquare(const Vector2& _vec) {
	return (_vec.x*_vec.x) + (_vec.y*_vec.y);
}

float Vector2::distance(const Vector2& _pos1, const Vector2& _pos2) {
	return sqrtf(distanceSquare(_pos1, _pos2));
}

float Vector2::distanceSquare(const Vector2& _pos1, const Vector2& _pos2) {
	return (_pos1.x - _pos2.x)*(_pos1.x - _pos2.x) + (_pos1.y - _pos2.y)*(_pos1.y - _pos2.y);
}

Vector2 Vector2::normalize(const Vector2& _vec) {
	float vec_length = length(_vec);
	if (FloatEqual(vec_length, 0)) {
		return Vector2(0, 0);
	}
	return _vec / vec_length;
}

float Vector2::dot(const Vector2& _vec1, const Vector2& _vec2) {
	return _vec1.x*_vec2.x + _vec1.y*_vec2.y;
}

float Vector2::cross(const Vector2& _vec1, const Vector2& _vec2) {
	return _vec1.x*_vec2.y - _vec1.y*_vec2.x;
}

Vector2 Vector2::createWithAngleNorm(const float _angle, const float _norm) {
	return { cos(_angle)*_norm,sin(_angle)*_norm };
}

float Vector2::vector2ToAngle(const Vector2& _vec) {
	return atan2f(_vec.y, _vec.x);
}

Vector2 Vector2::clamp(const Vector2& _vec, const Vector2& _min, const Vector2& _max) {
	Vector2 vec = _vec;

	if (vec.x < _min.x) {
		vec.x =_min.x;
	}
	else if (vec.x > _max.x) {
		vec.x = _max.x;
	}

	if (vec.y < _min.y) {
		vec.y = _min.y;
	}
	else if (vec.y > _max.y) {
		vec.y =_max.y;
	}

	return vec;
}

Vector2 Vector2::rotate(const Vector2& _vec, const float _rad, const Vector2& _center) {
	Vector2 vec;
	vec.x = (_vec.x - _center.x) * cosf(_rad) - (_vec.y - _center.y) * sinf(_rad) + _center.x;
	vec.y = (_vec.x - _center.x) * sinf(_rad) + (_vec.y - _center.y) * cosf(_rad) + _center.y;
	return vec;
}

