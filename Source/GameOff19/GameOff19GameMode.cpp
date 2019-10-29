// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GameOff19GameMode.h"
#include "GameOff19HUD.h"
#include "GameOff19Character.h"
#include "UObject/ConstructorHelpers.h"

AGameOff19GameMode::AGameOff19GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGameOff19HUD::StaticClass();
}
