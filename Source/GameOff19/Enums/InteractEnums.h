// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreTypes.h"
#include "UObject/ObjectMacros.h"
#include "InteractEnums.generated.h"

UENUM(BlueprintType)
enum class EInteractType : uint8 {
	Bone,
	Socket
};

UENUM(BlueprintType)
enum class EHandType : uint8 {
	Left UMETA(DisplayName = "Left Hand"),
	Right  UMETA(DisplayName = "Right Hand")
};