// ©Playtypus Games 2015

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CPerlinNoiseUtility.generated.h"

/**
 * 
 */

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ENoiseQuality : uint8
{
	QUALITY_FAST 	UMETA(DisplayName = "Fast"),
	QUALITY_STD 	UMETA(DisplayName = "Standard"),
	QUALITY_BEST	UMETA(DisplayName = "Best")
};

UCLASS()
class BLUTENUNDLEVELN_API UCPerlinNoiseUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "CPerlinNoiseUtility")
		static void PerlinGetValue(const float &x, const float &y, const float &z, float &random);
	//Default values defined here?
	UFUNCTION(BlueprintPure, Category = "CPerlinNoiseUtility")
		static void PerlinGetValuePrecise(const float x, const float y, const float z, float &random, const float frequency = 1, const float lacunarity = 2, const ENoiseQuality quality = ENoiseQuality::QUALITY_FAST, const int32 octaveCount = 6, const float persistence = 0.5f, const int32 seed = 0);

};
