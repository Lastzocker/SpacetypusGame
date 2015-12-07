// ©Playtypus Games 2015

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CPerlinNoiseUtility.generated.h"

/**
 * 
 */
UCLASS()
class BLUTENUNDLEVELN_API UCPerlinNoiseUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "CMathUtility")
		static void PerlinTest(float &random);


};
