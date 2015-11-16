// ©Playtypus Games 2015

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CMathUtility.generated.h"

/**
 * 
 */
UCLASS()
class BLUTENUNDLEVELN_API UCMathUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	public:
	UFUNCTION(BlueprintCallable, Category = "CMathUtility")
		static int32 GetMaxIntValue();
	
	
};
