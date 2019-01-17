#include "MyMath.h"

bool FloatEqual(float a, float b) {
	return std::abs(a - b) <= std::numeric_limits<float>::epsilon();
}
