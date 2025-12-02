#include <iostream>
#include "AnimationBinaries.h"
#include <stdexcept>

int main()
{
	try
	{
		std::cout << ("Enter Location to your animation file of sf3 latest version : ");
		std::string path = "";
		std::cin >> path;
		FILE* inFile = fopen(path.c_str(), "rb");

		AnimationBinaries Binaries = AnimationBinaries::LoadFromFile(inFile);

		std::cout << ("\n\nTotal Number of Frames in the Animation:- ");
		std::cout << Binaries.framesCount;

		std::cout << ("\nTotal Number of Bones used in the Animation:- ");
		std::cout << Binaries.bonesIDsCount;

		std::cout << ("\nEnter the frame you want to see values of:- ");
		int32_t index = 0;
		std::cin >> index;

		if (index > Binaries.framesCount || index < 1)
		{
			throw std::invalid_argument("Frame Index entered does'nt exist.");
		}

		std::cout << ("\n\nFrame Number:- ");
		std::cout << index;
		std::cout << "\n";

		AnimationFrame frame = Binaries.frames[index - 1];

		for (int i = 0; i < Binaries.bonesIDsCount; i++)
		{
			for (int j = 0; j < Binaries.bonesIDsCount; j++)
			{
				if (Binaries.bonesIDs[j] == i)
				{
					std::cout << ("\nBoneId:- ");
					std::cout << i;

					AnimatedTransformCompressed TransformC = frame.bonesAnimation[j];

					Vector3 Position = TransformC._p.Position();
					Quaternion Rotation = TransformC._r.Rotation();

					printf("\nPosition: (%f, %f, %f)", Position.x, Position.y, Position.z);
					printf("\nQuaternion: (%f, %f, %f, %f)\n", Rotation.x, Rotation.y, Rotation.z, Rotation.w);
				}
			}
		}
	}
	catch (_exception e)
	{
		std::cout << ("Invalid Input Entered.");
	}
}