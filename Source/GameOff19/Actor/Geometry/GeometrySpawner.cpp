// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometrySpawner.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "GameOff19/Actor/Geometry/GeometryClass.h"

// Sets default values
AGeometrySpawner::AGeometrySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGeometrySpawner::BeginPlay()
{
	Super::BeginPlay();
	Internal_Init();

}


void AGeometrySpawner::Internal_Init()
{
	for (int i = 0; i < CubesToSpawn.Num(); i++)
	{
		FActorSpawnParameters params; params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
		AGeometryClass * NewCube = GetWorld()->SpawnActor<AGeometryClass>(CubesToSpawn[i], GetActorTransform(), params); // if doesnt work well, use deferred spawn
		if (NewCube)
		{
			NewCube->Internal_SetStatus(false); 
			NewCube->Internal_SetSpawner(this); 
			SpawnQueue.Add(NewCube);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AGeometrySpawner::TimerEvent, TimeBetweenSpawn, true, TimeBetweenSpawn);

}

void AGeometrySpawner::CubeDestroyed(AGeometryClass * DestroyedCube)
{
	DestroyedCube->Internal_SetStatus(false); 
	DestroyedCube->SetActorTransform( GetActorTransform() );
	SpawnQueue.Add(DestroyedCube);
	
	if (!GetWorld()->GetTimerManager().IsTimerActive(SpawnTimer))//If the timer is stopped, fires again
		GetWorld()->GetTimerManager().SetTimer(SpawnTimer,this, &AGeometrySpawner::TimerEvent, TimeBetweenSpawn, true, TimeBetweenSpawn);
}



void AGeometrySpawner::SetCanSpawnFlag(bool bFlagg)
{
	bCanSpawn = bFlagg; 
	if(bCanSpawn && !GetWorld()->GetTimerManager().IsTimerActive(SpawnTimer))//If the timer is stopped, fires again
		GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AGeometrySpawner::TimerEvent, TimeBetweenSpawn, true, TimeBetweenSpawn);
}

void AGeometrySpawner::SpawnCube(AGeometryClass * Cube)
{
	FTransform SpawnTransform = GetActorTransform(); 
	SpawnTransform.SetLocation(GetActorLocation() + FVector(FMath::RandRange(-100.0f,100.0f), FMath::RandRange(-100.0f, 100.0f),0));
	UE_LOG(LogTemp, Log, TEXT("Spawning cube at %s"), *SpawnTransform.GetLocation().ToString()); 
	Cube->SetActorTransform(SpawnTransform);
	Cube->Internal_SetStatus(true);
}

void AGeometrySpawner::TimerEvent()
{
	if (SpawnQueue.Num() && bCanSpawn)
	{
		SpawnCube(SpawnQueue[0]); 
		SpawnQueue.RemoveAt(0);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);
	}
}