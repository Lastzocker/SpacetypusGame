//©Playtypus Games 2015
//CVectorUtility erbt von BlueprintFunctionLibrary

#include "BlutenUndLeveln.h"
#include "CVectorUtility.h"


/*This function returns an aiming solution for a projectile fired with <bulletSpeed> from <muzzlePosition> at a target moving relative to the muzzle with <targetRelativeVelocity>
located at <targetPosition> at the time of firing. The solution is equation-based and disregards target acceleration to significantly reduce complexity.
*/
void UCVectorUtility::GetAimDirectionPrecise(const FVector &muzzlePosition, const FVector &targetPosition, const FVector &targetRelativeVelocity, const float &bulletSpeed,
	FVector &predictedAimVector, FVector &predictedTargetRelativePosition, float &timeToTarget)
{
	float D = (targetPosition - muzzlePosition).Size();
	float St = targetRelativeVelocity.Size();

	FVector targetVector = (muzzlePosition - targetPosition).GetSafeNormal();
	FVector targetSpeed = targetRelativeVelocity.GetSafeNormal();

	float cosTheta = FVector::DotProduct(targetVector, targetSpeed);

	float a = FMath::Pow(bulletSpeed, 2) - FMath::Pow(St, 2);
	float b = 2 * D * St * cosTheta;
	float c = -FMath::Pow(D, 2);

	float t1 = (-b + FMath::Sqrt(FMath::Pow(b, 2) - 4 * a * c)) / (2 * a);
	float t2 = (-b - FMath::Sqrt(FMath::Pow(b, 2) - 4 * a * c)) / (2 * a);

	if (t1 < 0 && t2 < 0) //If both t1 and t2 are below zero, the projectile will never reach the target.
	{
		timeToTarget = 0;
		predictedAimVector = FVector(0);
		predictedTargetRelativePosition = FVector(0);
		return;
	}
	else if (t1 < 0)
	{
		timeToTarget = t2;
	}
	else if (t2 < 0)
	{
		timeToTarget = t1;
	}
	else
	{
		timeToTarget = FMath::Min(t1, t2);
	}

	predictedAimVector = (targetRelativeVelocity + ((targetPosition - muzzlePosition) / timeToTarget)).GetSafeNormal();
	predictedTargetRelativePosition = targetRelativeVelocity * timeToTarget + targetPosition;
}

/*This alternative iterative solution approximates the <timeToTarget> value based on a forwarded starting value and also includes <targetAcceleration> into the computation.
The <iterations> parameter specifies the amount of iterations per function-call.

--!!!--
The value of <timeToTarget> is passed as a reference,the function will change the value of the variable provided as input into <timeToTarget> to a more correct value.
This enables an easy way of implementing the function to be processed over a number of time-steps, each time yielding a more precise approximation while reducing overhead.
The initial value of <timeToTarget> should be sufficiently close to the actual value, this can be achieved by feeding in the time it takes the projectile to reach the current <targetPosition>.

If the target changes or the function did not run for a while, the value of <timeToTarget> should be reset to the starting value.
This reset is automatically handled by the function when setting the value of <timeToTarget> to a value <= 0.
*/
void UCVectorUtility::GetAimDirectionIterative(const FVector &muzzlePosition, const FVector &targetPosition, const FVector &targetRelativeVelocity, const FVector &targetAcceleration, const float &bulletSpeed, const int32 &iterations,
	UPARAM(ref) float &timeToTarget, FVector &predictedAimVector, FVector &predictedTargetRelativePosition)
{
	if (timeToTarget <= 0)
	{
		GetTravelTimeToPoint(muzzlePosition, targetPosition, bulletSpeed, timeToTarget);
	}

	predictedTargetRelativePosition = targetPosition;

	for (int i = 0; i < iterations; i++)
	{
		predictedTargetRelativePosition = targetPosition + targetRelativeVelocity * timeToTarget + 0.5f * targetAcceleration * FMath::Pow(timeToTarget, 2);
		timeToTarget = (predictedTargetRelativePosition - muzzlePosition).Size() / bulletSpeed;
		if (timeToTarget >= 1000.0f) //Clamps the maximum value of the time it takes to reach the target and invalidates the solution
		{
			timeToTarget = 1000.0f;
			predictedAimVector = FVector(0);
			predictedTargetRelativePosition = FVector(0);
			return;
		}
	}

	predictedAimVector = (predictedTargetRelativePosition - muzzlePosition).GetSafeNormal();
}


//Returns the time it takes from <startPosition> to <endPosition> while travelling at constant <speed>
void UCVectorUtility::GetTravelTimeToPoint(const FVector &startPosition, const FVector &endPosition, const float &speed, float &travelTime)
{
	travelTime = (startPosition - endPosition).Size() / speed;
}

//Projects <aimVector> along the distance between <muzzlePosition> and <targetPosition>
void UCVectorUtility::GetTargetRadialOffsetVector(const FVector &aimVector, const FVector &muzzlePosition, const FVector &targetPosition, FVector &radialOffsetVector)
{
	radialOffsetVector = muzzlePosition + (aimVector * (targetPosition - muzzlePosition).Size());
}

//Calculate point of intersection between two lines. Does (currently) not work for vertical lines.
void UCVectorUtility::LineLineIntersection(const FVector2D &a1, const FVector2D &a2, const FVector2D &b1, const FVector2D &b2, FVector2D &intersectionPoint)
{
	if (a2.X - a1.X == 0 || b2.X - b1.X == 0)
	{
		return;
	}
	float am = (a2.Y - a1.Y) / (a2.X - a1.X);
	float bm = (b2.Y - b1.Y) / (b2.X - b1.X);

	float ac = a1.Y - am * a1.X;
	float bc = b1.Y - bm * b1.X;

	intersectionPoint.X = (bc - ac) / (am - bm);
	intersectionPoint.Y = am * intersectionPoint.X + ac;
}

//Projects a target point against the screen border. Assumes horizontally centered origin. (Probably should be optimized)
void UCVectorUtility::ProjectToScreenBorder(const FVector &originLocation, const FVector &targetLocation, const APlayerController *player, FVector2D &projectedPosition)
{
	FVector2D viewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

	FVector2D originPosition;
	FVector2D targetPosition;
	player->ProjectWorldLocationToScreen(originLocation, originPosition);
	player->ProjectWorldLocationToScreen(targetLocation, targetPosition);

	FVector2D targetDirection = targetPosition - originPosition;
	FVector2D upperRightDirection = (FVector2D(viewportSize.X, 0) - originPosition).GetSafeNormal();

	float mTarget = targetDirection.Y / targetDirection.X;
	float cTarget = targetPosition.Y - mTarget * targetPosition.X;

	FVector2D screenUpperRightDirection = (FVector2D(viewportSize.X, 0) - originPosition).GetSafeNormal();
	FVector2D screenLowerRightDirection = (FVector2D(viewportSize.X, viewportSize.Y) - originPosition).GetSafeNormal();

	targetDirection = targetDirection.GetSafeNormal();

	if (targetDirection.Y < screenUpperRightDirection.Y)
	{
		projectedPosition.X = -(cTarget / mTarget);
		projectedPosition.Y = 0;
	}
	else if (targetDirection.Y > screenLowerRightDirection.Y)
	{
		projectedPosition.X = (viewportSize.Y - cTarget) / mTarget;
		projectedPosition.Y = viewportSize.Y;
	}
	else if (targetDirection.X < 0)
	{
		projectedPosition.X = 0;
		projectedPosition.Y = cTarget;
	}
	else
	{
		projectedPosition.X = viewportSize.X;
		projectedPosition.Y = mTarget * viewportSize.X + cTarget;
	}
}

void UCVectorUtility::ConvertToMapSpace(const FVector &worldLocation, const FVector &playerLocation, const FVector2D &mapOriginPosition, const float &mapRadius, const float &ratio, const APlayerController *player, FVector2D &mapPosition, bool &inRange)
{
	FVector2D locationInScreenSpace;
	FVector2D playerLocationInScreenSpace;
	player->ProjectWorldLocationToScreen(worldLocation, locationInScreenSpace);
	player->ProjectWorldLocationToScreen(playerLocation, playerLocationInScreenSpace);

	mapPosition = ((locationInScreenSpace - playerLocationInScreenSpace) / ratio) + mapOriginPosition;

	if ((mapPosition - mapOriginPosition).Size() < mapRadius)
	{
		inRange = true;
	}
	else
	{
		inRange = false;
	}
}