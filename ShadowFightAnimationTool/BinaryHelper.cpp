#include "BinaryHelper.h"
#include <stdexcept>
#include <algorithm>

BinaryHelper::BinaryHelper(FILE* inFile, int LoopIndex, int Num)
{
	this->inFile = inFile;
	this->uShortArray = new uint16_t[Num];
	this->LoopIndex = LoopIndex;
	this->BufferSize = Num;
}

uint16_t BinaryHelper::ReturnShort()
{
	int Index = this->Threshold;

	if (Index == this->LoopIndex)
	{
		throw std::out_of_range("Reading over the ushort buffer threshold.");
	}

	if (this->BufferSize == 0)
	{
		throw std::invalid_argument("Buffer is Null.");
	}

	if (Index % this->BufferSize == 0)
	{
		int Min = std::min(BufferSize, this->LoopIndex - this->Threshold);

		fread(this->uShortArray, sizeof(uint16_t), Min, this->inFile);
	}
	int Offset = Index % this->BufferSize;

	if (Offset >= this->BufferSize)
	{
		throw std::invalid_argument("Offset out of Buffer Bounds.");
	}
	
	uint16_t value = this->uShortArray[Offset];

	this->Threshold++;

	return value;
}