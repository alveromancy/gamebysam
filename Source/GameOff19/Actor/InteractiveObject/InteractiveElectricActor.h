// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Utils/ElectricityActor.h"
#include "InteractiveElectricActor.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActivate, bool, bIsElectrified); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeactivate, bool, bIsElectrified);
UCLASS()
class GAMEOFF19_API UInteractiveElectricActor : public UElectricityActor
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		virtual void InteractiveActivate();

	UFUNCTION(BlueprintCallable)
		virtual void InteractiveDeactivate();

	UFUNCTION(BlueprintCallable, Category = "Info")
		bool IsActivated()const { return bIsActivated; }

protected:
	virtual void PropagateElectricity()override;

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Properties")
		bool bIsActivated;
	
	UPROPERTY(BlueprintAssignable)
		FOnActivate OnActivate;
	UPROPERTY(BlueprintAssignable)
		FOnDeactivate OnDeactivate;
};
