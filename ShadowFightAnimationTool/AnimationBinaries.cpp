#include "AnimationBinaries.h"
#include <stdexcept>
#include "BinaryHelper.h"

AnimationBinaries AnimationBinaries::LoadFromFile(FILE* inFile)
{
	AnimationBinaries animationBinaries = AnimationBinaries();

	long long Header = 0;
	fread(&Header, sizeof(long long), 1, inFile);

	if (Header != 457546134634734LL)
	{
		throw std::invalid_argument("Wrong animation file type");
	}

	int16_t ArrayCount = 0;
	fread(&ArrayCount, sizeof(int16_t), 1, inFile);

	long long* garbageBuffer = (long long*)malloc(sizeof(long long) * ArrayCount);
	fread(garbageBuffer, sizeof(long long), (int32_t)ArrayCount, inFile);

	animationBinaries.LoadAnimation(inFile);

	if (ArrayCount >= 2)
	{
		AnimationBinaries Tangents = AnimationBinaries();
		Tangents.LoadAnimation(inFile);

		animationBinaries.animationTangents = &Tangents;
	}

	return animationBinaries;
}

void AnimationBinaries::LoadAnimation(FILE* inFile)
{
	this->framesCount = 0;
	fread(&this->framesCount, sizeof(int32_t), 1, inFile);

	this->frames = (AnimationFrame*)malloc(sizeof(AnimationFrame) * this->framesCount);

	this->bonesIDsCount = 0;
	fread(&this->bonesIDsCount, sizeof(int32_t), 1, inFile);
	
	this->bonesIDs = (int16_t*)malloc(sizeof(int16_t) * this->bonesIDsCount);
	fread(this->bonesIDs, sizeof(int16_t), this->bonesIDsCount, inFile);

	BinaryHelper Helper = BinaryHelper(inFile, this->framesCount * this->bonesIDsCount * 6, 216);

	for (int i = 0; i < this->framesCount; i++)
	{
		this->frames[i] = AnimationFrame();
		this->frames[i].bonesAnimation = (AnimatedTransformCompressed*)malloc(sizeof(AnimatedTransformCompressed) * bonesIDsCount);

		for (int j = 0; j < this->bonesIDsCount; j++)
		{
			uint16_t _px = Helper.ReturnShort();
			uint16_t _py = Helper.ReturnShort();
			uint16_t _pz = Helper.ReturnShort();

			uint16_t _ux = Helper.ReturnShort();
			uint16_t _uy = Helper.ReturnShort();
			uint16_t _uz = Helper.ReturnShort();

			this->frames[i].bonesAnimation[j] = AnimatedTransformCompressed(_px, _py, _pz, _ux, _uy, _uz);
		}
	}
}