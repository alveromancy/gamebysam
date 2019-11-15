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
	//float m = FMath::Sqrt(2.f + 2.f * FVector::DotProduct(A, B)); //http://lolengine.net/blog/2013/09/18/beautiful-maths-quaternion-from-vectors
	//FVector w = (1.f / m) * FVector::CrossProduct(A, B);
	//return FQuat(w.X, w.Y, w.Z, 0.5f*m);

	float real_part = 1.f + FVector::DotProduct(A, B);
	FVector w;

	if (real_part < 1.e-6f)
	{
		/* If u and v are exactly opposite, rotate 180 degrees
		 * around an arbitrary orthogonal axis. Axis normalisation
		 * can happen later, when we normalise the quaternion. */
		real_part = 0.0f;
		w = abs(A.X) > abs(A.Z) ? FVector(-A.Y, A.X, 0.f)
			: FVector(0.f, -A.Z, A.Y);
	}
	else
	{
		/* Otherwise, build quaternion the standard way. */
		w = FVector::CrossProduct(A, B);
	}
	FQuat result(w.X, w.Y, w.Z, real_part);
	result.Normalize();
	return result; 
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

