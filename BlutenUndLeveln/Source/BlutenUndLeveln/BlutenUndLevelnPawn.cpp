// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "BlutenUndLeveln.h"
#include "BlutenUndLevelnPawn.h"
#include "BlutenUndLevelnProjectile.h"
#include "TimerManager.h"
#include "EngineUtils.h"

const FName ABlutenUndLevelnPawn::MoveForwardBinding("MoveForward");
const FName ABlutenUndLevelnPawn::MoveRightBinding("MoveRight");
const FName ABlutenUndLevelnPawn::FireForwardBinding("FireForward");
const FName ABlutenUndLevelnPawn::FireRightBinding("FireRight");
const FName ABlutenUndLevelnPawn::TurnBinding("Turn");

ABlutenUndLevelnPawn::ABlutenUndLevelnPawn()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	//ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);

	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	//Camera anchor point, acts as the cameras target transform 
	CameraAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("CameraAnchor"));
	CameraAnchor->AttachTo(RootComponent);
	CameraAnchor->RelativeRotation = FRotator(0, -70.f, 0);
	CameraAnchor->RelativeLocation = FVector(0, 0, 900.f);


	//Camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));

	CameraTransform = CameraAnchor->GetRelativeTransform();

	CameraLocationSmoothing = 0.05f;
	CameraRotationSmoothing = 0.05f;

	// Movement
	MoveSpeed = 1000.0f;

	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;

	ShipMeshComponent->SetSimulatePhysics(true);

	TurnSpeed = 20000.f;

	ProjectileSpeed = 1500.f;

	MaxHullIntegrity = 1000.f;

	HullIntegrity = MaxHullIntegrity;

}

void ABlutenUndLevelnPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);

	// set up gameplay key bindings
	InputComponent->BindAxis(MoveForwardBinding);
	InputComponent->BindAxis(MoveRightBinding);
	InputComponent->BindAxis(FireForwardBinding);
	InputComponent->BindAxis(FireRightBinding);
	InputComponent->BindAxis(TurnBinding);

	//InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ABlutenUndLevelnPawn::FireShot);
	//InputComponent->BindAction("FindTarget", EInputEvent::IE_Pressed, this, &ABlutenUndLevelnPawn::FindTarget);
}

void ABlutenUndLevelnPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/*
	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);
	const float TurnValue = GetInputAxisValue(TurnBinding);


	//Turning
	ShipMeshComponent->AddAngularImpulse(FVector(0, 0, TurnValue * TurnSpeed));

	//Movement
	if (ForwardValue > 0)
	{
		ShipMeshComponent->AddForce(ForwardValue * ThrusterForce * GetActorForwardVector());
	}
	else
	{
		ShipMeshComponent->AddForce(ForwardValue * ThrusterForce * GetActorForwardVector() * BackwardsMultiplier);
	}
	ShipMeshComponent->AddForce(RightValue * ThrusterForce * GetActorRightVector() * SidewaysMultiplier);
	*/
	//UpdateCameraLocation
	CameraTransform = FTransform(
		FMath::Lerp(CameraTransform.GetRotation().Rotator(), CameraAnchor->GetComponentRotation(), CameraRotationSmoothing),
		FMath::Lerp(CameraTransform.GetLocation(), CameraAnchor->GetComponentLocation(), CameraLocationSmoothing),
		FVector(1));

	CameraComponent->SetWorldTransform(CameraTransform);
}

void ABlutenUndLevelnPawn::FireShot()
{
	// If we it's ok to fire again
	if (bCanFire == true)
	{
		FVector FireDirection = GetActorForwardVector();
		// Spawn projectile at an offset from this pawn
		const FVector SpawnLocation = GetActorLocation(); //+ FireRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			// spawn the projectile
			ABlutenUndLevelnProjectile *NewProjectile = World->SpawnActor<ABlutenUndLevelnProjectile>(SpawnLocation, GetActorRotation());
			NewProjectile->Launch((ProjectileSpeed * FireDirection) + GetVelocity(), ProjectileLifetime);
			NewProjectile->GetProjectileMesh()->IgnoreActorWhenMoving(NewProjectile, true);
		}

		bCanFire = false;
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ABlutenUndLevelnPawn::ShotTimerExpired, FireRate);

		// try and play the sound if specified
		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		bCanFire = false;
	}
}

void ABlutenUndLevelnPawn::ShotTimerExpired()
{
	bCanFire = true;
}

void ABlutenUndLevelnPawn::FindTarget()
{
	UE_LOG(LogTemp, Warning, TEXT("Searching for target"));
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->ActorHasTag("Target"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Target found: %s"), *ActorItr->GetName());
			TargetActor = *ActorItr;
			return;
		}
	}
}

void ABlutenUndLevelnPawn::MoveForward(float Value)
{
	if (Value > 0)
	{
		ShipMeshComponent->AddForce(Value * ThrusterForce * GetActorForwardVector());
	}
	else
	{
		ShipMeshComponent->AddForce(Value * ThrusterForce * GetActorForwardVector() * BackwardsMultiplier);
	}
}

void ABlutenUndLevelnPawn::MoveRight(float Value)
{
	ShipMeshComponent->AddForce(Value * ThrusterForce * GetActorRightVector() * SidewaysMultiplier);
}

void ABlutenUndLevelnPawn::Turn(float Value)
{
	ShipMeshComponent->AddAngularImpulse(FVector(0, 0, Value * TurnSpeed));
}