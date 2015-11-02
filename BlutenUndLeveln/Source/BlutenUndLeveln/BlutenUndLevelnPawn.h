// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameFramework/Character.h"
#include "BlutenUndLevelnPawn.generated.h"

UCLASS(Blueprintable)
class ABlutenUndLevelnPawn : public APawn
{
	GENERATED_BODY()

		/* The mesh component */
		UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipMeshComponent;

	/** The camera */
	/*UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;*/

	/** Camera boom positioning the camera above the character */
	/*UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;*/

	/*UPROPERTY(Category = Scene, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* CameraAnchor;*/

public:
	ABlutenUndLevelnPawn();

	/** Offset from the ships location to spawn projectiles */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		FVector GunOffset;

	/* How fast the weapon will fire */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FireRate;

	/* The speed our ship moves around the level */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float MoveSpeed;

	/* The ship's "health" */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float HullIntegrity;

	/* The ship's maximum "health" */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float MaxHullIntegrity;

	/** Sound to play each time we fire */
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* FireSound;

	/* Thruster Force*/
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float ThrusterForce;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float SidewaysMultiplier;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float BackwardsMultiplier;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float TurnSpeed;

	/*Target*/
	UPROPERTY(Category = Targeting, EditAnywhere, BlueprintReadWrite)
		AActor* TargetActor;

	/*Projectile*/
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float ProjectileSpeed;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float ProjectileLifetime;

	/*Camera smoothing*/
	UPROPERTY(Category = Viewport, EditAnywhere, BlueprintReadWrite)
		float CameraLocationSmoothing;

	UPROPERTY(Category = Viewport, EditAnywhere, BlueprintReadWrite)
		float CameraRotationSmoothing;

	UPROPERTY(Category = Internal, BlueprintReadWrite)
		float ForwardThrust;

	UPROPERTY(Category = Internal, BlueprintReadWrite)
		float BackwardThrust;

	UPROPERTY(Category = Internal, BlueprintReadWrite)
		float LeftThrust;

	UPROPERTY(Category = Internal, BlueprintReadWrite)
		float RightThrust;

	// Begin Actor Interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End Actor Interface


	/* Handler for the fire timer expiry */
	void ShotTimerExpired();

	//Input events
	UFUNCTION(BlueprintCallable, Category = "ShipActions")
	void MoveForward(float Value);

	UFUNCTION(BlueprintCallable, Category = "ShipActions")
	void MoveRight(float Value);

	UFUNCTION(BlueprintCallable, Category = "ShipActions")
	void Turn(float Value);

	UFUNCTION(BlueprintCallable, Category = "ShipActions")
	void FindTarget();

	UFUNCTION(BlueprintCallable, Category = "ShipActions")
	void FireShot();

	// Static names for axis bindings
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireForwardBinding;
	static const FName FireRightBinding;
	static const FName TurnBinding;

private:

	/* Flag to control firing  */
	uint32 bCanFire : 1;

	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;

	FTransform CameraTransform;

public:
	/** Returns ShipMeshComponent subobject **/
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
	/** Returns CameraComponent subobject **/
	/*FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }*/
	/** Returns CameraBoom subobject **/
	/*FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }*/
};

