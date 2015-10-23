// ©Playtypus Games 2015

#pragma once

#include "GameFramework/PlayerController.h"
#include "BuLPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BLUTENUNDLEVELN_API ABuLPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void SetupInputComponent() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void PressedFire();
	void PressedFindTarget();
	
	
};
