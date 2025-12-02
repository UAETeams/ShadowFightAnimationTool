#pragma once
#include <cstdio>
#include <inttypes.h>

class BinaryHelper
{
private:
	FILE* inFile;
	int LoopIndex;
	uint16_t* uShortArray;
	int BufferSize;
	int Threshold;

public:
	BinaryHelper(FILE*, int, int);

	uint16_t ReturnShort();
};