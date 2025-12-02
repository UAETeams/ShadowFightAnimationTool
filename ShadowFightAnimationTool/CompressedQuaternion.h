#pragma once
#include <inttypes.h>
#include "CompressedQuaternion.h"
#include "Quaternion.h"

class CompressedQuaternion
{
public:
	uint16_t _v0;
	uint16_t _v1;
	uint16_t _v2;

	static struct staticField
	{
		float _maxValue = 1.4142135f;
		float _maxValueShift = 0.70710677f;
	};

	CompressedQuaternion(uint16_t v0, uint16_t v1, uint16_t v2);
	CompressedQuaternion() = default;

	Quaternion Rotation();
};
