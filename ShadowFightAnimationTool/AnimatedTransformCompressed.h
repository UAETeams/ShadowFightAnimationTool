#pragma once
#include "CompressedQuaternion.h"
#include "CompressedVector3.h"

class AnimatedTransformCompressed
{
public:
	CompressedQuaternion _r;
	CompressedVector3 _p;
public:
	AnimatedTransformCompressed(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);
	AnimatedTransformCompressed() = default;
};