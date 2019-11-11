// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Math3DLib.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FReflectionRayMath
{
	GENERATED_BODY()

};

UCLASS()
class GAMEOFF19_API UMath3DLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public: 
		/**
			Given the original ray direction and the normal, it computes the rotation axis and the angle to rotate in order to get the reflection ray
			Warning: Vectors must be normalized. 

			@param RayDirection Direction of the origin ray
			@param Normal Normal vector of the impact surface. 
			@return Reflected Ray direction 
		*/
		UFUNCTION(BlueprintCallable, Category = "Reflection")
		static FVector CalculateReflectionRay(const FVector &RayDirection, const FVector& Normal);

		UFUNCTION(BlueprintCallable, Category = "Rotation")
		static FQuat CalculateQuaternionBetweenVectors(const FVector & A, const FVector & B);

#if WITH_EDITOR
		UFUNCTION(BlueprintCallable, Category = "Ray")
			static void DebugVisualRay(const UWorld * World, const FVector & Origin, const FVector & End, const FColor & Color , float lifetime = -1);
#endif // WITH_EDITOR

		
};
