// ©Playtypus Games 2015

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine.h"
#include "CVectorUtility.generated.h"

/**
 * 
 */
UCLASS()
class BLUTENUNDLEVELN_API UCVectorUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "CVectorUtility")
		static void GetAimDirectionPrecise(const FVector &muzzlePosition, const FVector &targetPosition, const FVector &targetRelativeVelocity, const float &bulletSpeed,
		FVector &predictedAimVector, FVector &predictedTargetRelativePosition, float &timeToTarget);

	UFUNCTION(BlueprintCallable, Category = "CVectorUtility")
		static void GetAimDirectionIterative(const FVector &muzzlePosition, const FVector &targetPosition, const FVector &targetRelativeVelocity, const FVector &targetAcceleration, const float &bulletSpeed, const int32 &iterations,
		UPARAM(ref) float &timeToTarget, FVector &predictedAimVector, FVector &predictedTargetRelativePosition);

	UFUNCTION(BlueprintCallable, Category = "CVectorUtility")
		static void GetTravelTimeToPoint(const FVector &startPosition, const FVector &endPosition, const float &speed, float &travelTime);

	UFUNCTION(BlueprintCallable, Category = "CVectorUtility")
		static void GetTargetRadialOffsetVector(const FVector &aimVector, const FVector &muzzlePosition, const FVector &targetPosition, FVector &radialOffsetVector);

	UFUNCTION(BlueprintCallable, Category = "CVectorUtility")
		static void LineLineIntersection(const FVector2D &a1, const FVector2D &a2, const FVector2D &b1, const FVector2D &b2, FVector2D &intersectionPoint);

	UFUNCTION(BlueprintCallable, Category = "CVectorUtility")
		static void ProjectToScreenBorder(const FVector &originLocation, const FVector &targetLocation, const APlayerController *player, FVector2D &projectedPosition);

	UFUNCTION(BlueprintCallable, Category = "CVectorUtility")
		static void ConvertToMapSpace(const FVector &worldLocation, const FVector &playerLocation, const FVector2D &mapOriginPosition, const float &mapRadius, const float &ratio, const APlayerController *player, FVector2D &mapPosition, bool &inRange);
};
