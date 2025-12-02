#pragma once
#include "AnimationFrame.h"

class AnimationBinaries
{
private:
	void LoadAnimation(FILE*);

public:
	AnimationFrame* frames;
	int framesCount;

	int16_t* bonesIDs;
	int bonesIDsCount;

	AnimationBinaries* animationTangents;

	static AnimationBinaries LoadFromFile(FILE*);

	AnimationBinaries() = default;
};