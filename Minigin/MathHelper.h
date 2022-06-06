#pragma once
#include <corecrt_math.h>

template<typename t>
static t Magnitude(const glm::vec3& vector)
{
	return static_cast<t>(sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z));
}
