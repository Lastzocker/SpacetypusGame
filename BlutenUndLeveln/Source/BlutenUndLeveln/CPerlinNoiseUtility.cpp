// ©Playtypus Games 2015


#include "BlutenUndLeveln.h"
#include "CPerlinNoiseUtility.h"
#include <iostream>
#include <noise.h>

void UCPerlinNoiseUtility::PerlinGetValue(const float &x, const float &y, const float &z, float &random)
{
	noise::module::Perlin myModule;
	double value = myModule.GetValue(x, y, z);
	random = value;

	
	/*FString filePath = FPaths::Combine(*FPaths::GameDir(), TEXT("ThirdParty/Libnoise/Libraries/"), TEXT("LibnoiseDLL.dll")); // Concatenate the plugins folder and the DLL file.
	if (FPaths::FileExists(filePath))
	{
		void *DLLHandle;
		DLLHandle = FPlatformProcess::GetDllHandle(*filePath); // Retrieve the DLL.
		if (DLLHandle != NULL)
		{
			MyMathFuncs DLLgetCircleArea = NULL; // Local DLL function pointer.
			FString procName = "PerlinGetValue"; // The exact name of the DLL function.
			DLLgetCircleArea = (MyMathFuncs)FPlatformProcess::GetDllExport(DLLHandle, *procName); // Export the DLL function.
			if (DLLgetCircleArea != NULL)
			{
				float out = DLLgetCircleArea(radius); // Call the DLL function, with arguments corresponding to the signature and return type of the function.
				return out; // return to UE
			}
		}
	}
	random = 1.0f;*/
}

void UCPerlinNoiseUtility::PerlinGetValuePrecise(const float x, const float y, const float z, float &random, const float frequency, const float lacunarity, const ENoiseQuality quality, const int32 octaveCount, const float persistence, const int32 seed)
{
	noise::module::Perlin myModule;

	//Change the noise parameters if they're not at their default values
	if (frequency!=1)
	{
		myModule.SetFrequency(frequency);
	}
	if (lacunarity!=2)
	{
		myModule.SetLacunarity(lacunarity);
	}
	myModule.SetNoiseQuality((noise::NoiseQuality)quality); //Todo: Check if this actually works
	if (octaveCount!=6)
	{
		myModule.SetOctaveCount(octaveCount);
	}
	if (persistence!=0.5f)
	{
		myModule.SetPersistence(persistence);
	}
	if (seed!=0)
	{
		myModule.SetSeed(seed);
	}

	double value = myModule.GetValue(x, y, z);
	random = value;
}