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

	for (int32 i = 0; i < CubesToSpawn.Num(); i++)
		SpawnQueue.Add(CubesToSpawn[i].GetDefaultObject()); 


	if (SpawnQueue.Num())
		GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AGeometrySpawner::TimerEvent, TimeBetweenSpawn, true, TimeBetweenSpawn);

}

void AGeometrySpawner::CubeDestroyed(AGeometryClass * DestroyedCube, bool bShouldRespawn)
{
	if (bShouldRespawn)
	{
		//AGeometryClass * newCube = GetWorld()->SpawnActorDeferred<AGeometryClass>()
		//AddCubeToSpawnQueue(DestroyedCube);
	}
		

}


void AGeometrySpawner::SpawnCube(AGeometryClass * Cube)
{

}

void AGeometrySpawner::TimerEvent()
{

}