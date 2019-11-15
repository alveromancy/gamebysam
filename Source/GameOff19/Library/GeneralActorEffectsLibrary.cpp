// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralActorEffectsLibrary.h"
#include "GameFramework/WorldSettings.h"
#include "GameFramework/Actor.h"


void UGeneralActorEffectsLibrary::SetGlobalTimeSpeed(AWorldSettings * WorldSettings, float Percent, bool bAfffectsPlayer, AActor * Player)
{
	float NewSpeed = NormalizePercent(Percent); 
	WorldSettings->SetTimeDilation(NewSpeed);
	if (!bAfffectsPlayer && Player)
		Player->CustomTimeDilation = 1 / NewSpeed;
}


void UGeneralActorEffectsLibrary::ResetTimeSpeed(AWorldSettings * WorldSettings, bool bAfffectsPlayer, AActor * Player)
{
	WorldSettings->SetTimeDilation(1);
	if (!bAfffectsPlayer && Player)
		Player->CustomTimeDilation = 1 ;
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