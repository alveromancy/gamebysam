// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreTypes.h"
#include "UObject/ObjectMacros.h"
#include "InteractEnums.generated.h"

UENUM(BlueprintType)
enum class EInteractType : uint8 {
	Interact,
	PickUp
};