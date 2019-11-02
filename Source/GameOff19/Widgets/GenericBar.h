// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GenericBar.generated.h"

/**
 * 
 */


UCLASS()
class GAMEOFF19_API UGenericBar : public UUserWidget
{
	GENERATED_BODY()

public: 

	//Updates the widget to the new value
	void Update(float NewValue); 

	UFUNCTION(BlueprintImplementableEvent)
		void OnBarIncrease(float DeltaIncrement); 

	UFUNCTION(BlueprintImplementableEvent)
		void OnBarDecease(float DeltaDecresae);


protected: 

	UPROPERTY(BlueprintReadOnly)
		float value;
	
};
