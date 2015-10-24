// ©Playtypus Games 2015

#include "BlutenUndLeveln.h"
#include "BuLPlayerController.h"
#include "BlutenUndLevelnPawn.h"


//Inputs
void ABuLPlayerController::SetupInputComponent(){

	Super::SetupInputComponent();

	check(InputComponent);

	if (InputComponent != NULL)
	{
		//InputComponent->BindAxis("MoveUp", this, &AMyPlayerController::MoveUp);
		InputComponent->BindAxis("MoveForward", this, &ABuLPlayerController::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &ABuLPlayerController::MoveRight);
		InputComponent->BindAxis("Turn", this, &ABuLPlayerController::Turn);

		InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ABuLPlayerController::PressedFire);
		InputComponent->BindAction("FindTarget", EInputEvent::IE_Pressed, this, &ABuLPlayerController::PressedFindTarget);
	}
}

void ABuLPlayerController::MoveForward(float Value)
{
	if (GetPawn() != NULL)
	{
		Cast<ABlutenUndLevelnPawn>(GetPawn())->MoveForward(Value);
	}
}

void ABuLPlayerController::MoveRight(float Value)
{
	if (GetPawn() != NULL)
	{
		Cast<ABlutenUndLevelnPawn>(GetPawn())->MoveRight(Value);
	}
}

void ABuLPlayerController::Turn(float Value)
{
	if (GetPawn() != NULL)
	{
		Cast<ABlutenUndLevelnPawn>(GetPawn())->Turn(Value);
	}
}

void ABuLPlayerController::PressedFire()
{
	if (GetPawn()!=NULL)
	{
		Cast<ABlutenUndLevelnPawn>(GetPawn())->FireShot();
	}
}

void ABuLPlayerController::PressedFindTarget()
{
	if (GetPawn() != NULL)
	{
		Cast<ABlutenUndLevelnPawn>(GetPawn())->FindTarget();
	}
}
