#pragma once
class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;
public:
	Quaternion(float, float, float, float);
	Quaternion() = default;
};