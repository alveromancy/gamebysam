// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GeneralActorEffectsLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF19_API UGeneralActorEffectsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public: 
	UFUNCTION(BlueprintCallable)
		static void SetGlobalTimeSpeed(class AWorldSettings * WorldSettings, float Percent, bool bAfffectsPlayer = false, class AActor * Player = nullptr);

	UFUNCTION(BlueprintCallable)
		static void ResetTimeSpeed(class AWorldSettings * WorldSettings , bool bAfffectsPlayer = false, class AActor * Player = nullptr);

	UFUNCTION(BlueprintCallable)
		static void SetOnlyPlayerTimeSpeed(class AActor * Player, float Percent);


	UFUNCTION(BlueprintCallable)
		static void ResetPlyerTimeSpeed(class AActor * Player, float Percent);

private: 

	static float NormalizePercent(const float & Percent); 
};
