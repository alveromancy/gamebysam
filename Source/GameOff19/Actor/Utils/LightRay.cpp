// Fill out your copyright notice in the Description page of Project Settings.


#include "LightRay.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"



// Sets default values
ALightRay::ALightRay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SM_Mesh->SetCollisionProfileName("Ray");
	RootComponent = SM_Mesh;
	SM_Mesh->SetWorldScale3D(FVector(0.2));
}


void ALightRay::PostActorCreated()
{
	Super::PostActorCreated();

	if (!HasAllFlags(RF_Transient)) //We only want to run this code when the final actor is created 
	{
		RecalculateRayLenght();
	}
}


#if WITH_EDITOR
void ALightRay::PostEditMove(bool bFinished)
{
	Super::PostEditMove(bFinished);

	if (bFinished) //Mosue button is not clicked anymore
	{
		RecalculateRayLenght();
	}

}
#endif


// Called when the game starts or when spawned
void ALightRay::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(true);
	OriginalScaleFactor = GetActorScale3D();
}

// Called every frame
void ALightRay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	RecalculateRayLenght();

}


FHitResult ALightRay::RecalculateRayLenght()
{
	FHitResult Hit; 
	if (RayTrace(Hit))
	{
		FVector CurrentScale = GetActorScale3D();
		//CurrentScale.Z = (Hit.Distance / 100) + 0.1;
		CurrentScale.Z = (Hit.Distance + CurrentScale.X*50) / 100;
		SetActorScale3D(CurrentScale);
	}
			
	return Hit; 
}



bool ALightRay::RayTrace(FHitResult & OutHit)
{
	FVector StartPoint = GetActorLocation(); 

	FVector EndPoint =  StartPoint + GetActorUpVector() * LIGHT_MAXIMUM_DISTANCE;
	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel3; //RayTrace Trace created on physics channels 
	FCollisionQueryParams CQP; CQP.bFindInitialOverlaps = false; CQP.AddIgnoredActor(this);
	FCollisionResponseParams CRP; 

	bool bHasImpact = GetWorld()->LineTraceSingleByChannel(OutHit, StartPoint, EndPoint,Channel, CQP,CRP);


	return bHasImpact;
}

