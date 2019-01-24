#pragma once

#include <cmath>
#include <limits>
#include <assert.h>


constexpr float PI  = DX_PI_F;
constexpr float PI2 = DX_TWO_PI_F;


template <class T> T ClampT(T num, const T min, const T max) {
	assert(min < max);
	if (num < min) {
		return min;
	}
	else if (num > max) {
		return max;
	}
	return num;
}

bool FloatEqual(float a, float b);
