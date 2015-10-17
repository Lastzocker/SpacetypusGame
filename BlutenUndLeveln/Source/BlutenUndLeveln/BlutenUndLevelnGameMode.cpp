// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "BlutenUndLeveln.h"
#include "BlutenUndLevelnGameMode.h"
#include "BlutenUndLevelnPawn.h"

ABlutenUndLevelnGameMode::ABlutenUndLevelnGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ABlutenUndLevelnPawn::StaticClass();
}

void ABlutenUndLevelnGameMode::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Game started"));

	APlayerController *MyPlayerController = GetWorld()->GetFirstPlayerController();

	MyPlayerController->bShowMouseCursor = true;

	Super::BeginPlay();
}