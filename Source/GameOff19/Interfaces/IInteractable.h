// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums/InteractEnums.h"
#include "IInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UIInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEOFF19_API IIInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Interactable)
	void Interact(EInteractType& interactType, EHandIKType& handIKType);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Interactable)
	FVector GetLeftInteractPoint() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Interactable)
	FVector GetRightInteractPoint() const;
};