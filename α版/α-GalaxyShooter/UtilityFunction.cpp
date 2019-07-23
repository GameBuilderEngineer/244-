#include "UtilityFunction.h"



UtilityFunction::UtilityFunction()
{
}


UtilityFunction::~UtilityFunction()
{
}

int UtilityFunction::wrap(int x, int low, int high)
{
	assert(low < high);
	const int n = (x - low) % (high - low);
	return (n >= 0) ? (n + low) : (n + high);
}

float UtilityFunction::wrap(float x, float low, float high)
{
	assert(low < high);
	const float n = std::fmod(x - low,high - low);
	return (n >= 0) ? (n + low) : (n + high);
}

template<typename T>
T UtilityFunction::clamp(T x, T low, T high) {
	assert(low <= high);
	T result = max(x, low);
	result = min(result, high);

	return result;
}