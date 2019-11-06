// Fill out your copyright notice in the Description page of Project Settings.


#include "LightRay.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "GameOff19/Library/Math3DLib.h"



const int32 ALightRay::LIGHT_MAXIMUM_DISTANCE = 50000;
const int32 ALightRay::MAX_REFLECTIONS = 1;
const float ALightRay::RADIUS_CONSTANT = 0.1f;

//Struct function

void FReflectionData::Debug(UWorld * World)
{
#if WITH_EDITOR	
	check(World);
	FVector EndPoint = ImpactPoint + ReflectedDirection * 500;
	FVector EndNormal = ImpactPoint + Normal * 500;
	DrawDebugLine(World, ImpactPoint, EndPoint, FColor::Red, false, 0.5f, 1, 5.0f);
	DrawDebugLine(World, ImpactPoint, EndNormal, FColor::Blue, false, 0.5f, 1, 5.0f);
#endif
}



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


void ALightRay::PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;


	if (PropertyName == GET_MEMBER_NAME_CHECKED(ALightRay, RayRadius))
	{
		FVector scale = GetActorScale3D(); 
		scale.X = scale.Y = RayRadius * RADIUS_CONSTANT;
		SetActorScale3D(scale); 
	}
}

#endif


// Called when the game starts or when spawned
void ALightRay::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(true);

}

// Called every frame
void ALightRay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RecalculateRayLenght();
}

void ALightRay::BeginDestroy()
{
	Super::BeginDestroy();
	if (ReflectedRay)
		ReflectedRay->Destroy();
}


FHitResult ALightRay::RecalculateRayLenght()
{
	FHitResult Hit; 
	if (RayTrace(Hit))
	{
		FVector CurrentScale = GetActorScale3D();
		CurrentScale.Z = (Hit.Distance + CurrentScale.X*50) / 100;
		SetActorScale3D(CurrentScale);
		
		if(true) //TODO Ask if hits the material and if the material cann reflect the light
			ReflectLight(Hit.ImpactPoint, Hit.ImpactNormal);
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


void ALightRay::ReflectLight(const FVector & ImpactPoint, const FVector & Normal)
{
	FReflectionData FrameReflection(ImpactPoint, Normal);
	if ( ReflectionIndex < MAX_REFLECTIONS && FrameReflection != CurrentReflection) //Check that our ray can reflect once more, and we are not repeating the relfection of previous frame
	{
		UE_LOG(LogTemp, Log, TEXT("Reflecting the light")); 
		FrameReflection.ReflectedDirection = UMath3DLib::CalculateReflectionRay(GetActorUpVector(), Normal);	
		
		if (ReflectedRay)
			ReflectedRay->Destroy();
		//ReflectedRay = SpawnReflectedLight(ImpactPoint, FrameReflection.ReflectedDirection);
		CurrentReflection = FrameReflection;
	}

	CurrentReflection.Debug(GetWorld());
}


ALightRay * ALightRay::SpawnReflectedLight(const FVector & ImpactPoint, const FVector & Direction)
{
	UE_LOG(LogTemp, Log, TEXT("Spawning light"));
	FQuat Rotation = UMath3DLib::CalculateQuaternionBetweenVectors(FVector(0,0,1), Direction);
	FTransform SpawnTransform(Rotation, ImpactPoint, FVector(RayRadius*RADIUS_CONSTANT));
	ALightRay * reflectedRay = GetWorld()->SpawnActorDeferred< ALightRay>(ALightRay::StaticClass(), SpawnTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (reflectedRay)
	{
		reflectedRay->SetRelfectionIndex(ReflectionIndex + 1);
		reflectedRay->FinishSpawning(SpawnTransform);
	}
	
	return reflectedRay;
}

