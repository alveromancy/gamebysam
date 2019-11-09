// Fill out your copyright notice in the Description page of Project Settings.


#include "Math3DLib.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


FVector UMath3DLib::CalculateReflectionRay(const FVector& RayDirection, const FVector& Normal)
{
	//Found Axis 
	FVector RotationAxis = FVector::CrossProduct(Normal , RayDirection);

	//Angle
	float DotProduct = FVector::DotProduct(-RayDirection, Normal);
	float degrees = FMath::Acos(DotProduct);
	degrees = FMath::RadiansToDegrees(degrees);

	//Calculate resulting vector
	FVector Reflected = Normal.RotateAngleAxis(degrees, RotationAxis);

	return Reflected;
}

FQuat UMath3DLib::CalculateQuaternionBetweenVectors(const FVector & A, const FVector & B)
{
	FVector RotationAxis = FVector::CrossProduct(B, A);
	float degrees = FMath::Acos(FVector::DotProduct(B, A) );

	return FQuat(RotationAxis, FMath::RadiansToDegrees(degrees));
}


#if WITH_EDITOR

void  UMath3DLib::DebugVisualRay(const UWorld * World, const FVector & Origin, const FVector & End, const FColor & Color, float lifetime)
{

	if (lifetime > 0)
		DrawDebugLine(World, Origin, End, Color, true);
	else
		DrawDebugLine(World, Origin, End, Color,false, lifetime, 1, 5.0f);
}

#endif // WITH_EDITOR

