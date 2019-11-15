// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralActorEffectsLibrary.h"
#include "GameFramework/WorldSettings.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"


void UGeneralActorEffectsLibrary::SetGlobalTimeSpeed(UWorld * World, float Percent, bool bAfffectsPlayer, AActor * Player)
{
	if (World)
	{
		float NewSpeed = NormalizePercent(Percent);
		World->GetWorldSettings()->SetTimeDilation(NewSpeed);
		if (!bAfffectsPlayer && Player)
			Player->CustomTimeDilation = 1 / NewSpeed;
	}

}


void UGeneralActorEffectsLibrary::ResetTimeSpeed( UWorld * World, bool bAfffectsPlayer, AActor * Player)
{
	if (World)
	{
		World->GetWorldSettings()->SetTimeDilation(1);
		if (!bAfffectsPlayer && Player)
			Player->CustomTimeDilation = 1;
	}

}


void UGeneralActorEffectsLibrary::SetOnlyPlayerTimeSpeed(AActor * Player, float Percent)
{
	float NewSpeed = NormalizePercent(Percent);
	Player->CustomTimeDilation = NewSpeed;
}


void UGeneralActorEffectsLibrary::ResetPlyerTimeSpeed(AActor * Player, float Percent)
{
	Player->CustomTimeDilation = 1; 
}


float UGeneralActorEffectsLibrary::NormalizePercent(const float & Percent)
{
	return  (Percent < 0) ? 0 : Percent;
}