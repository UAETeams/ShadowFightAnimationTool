#pragma once
#include "half.h"
#include "Vector3.h"

class CompressedVector3
{
private:
	float halftofloat(uint16_t);
public:
	uint16_t _px;
	uint16_t _py;
	uint16_t _pz;
public:
	CompressedVector3(uint16_t, uint16_t, uint16_t);
	CompressedVector3() = default;

	Vector3 Position();
};