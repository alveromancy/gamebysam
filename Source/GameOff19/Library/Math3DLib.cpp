// Fill out your copyright notice in the Description page of Project Settings.


#include "Math3DLib.h"
#include "Math/UnrealMathUtility.h"


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

