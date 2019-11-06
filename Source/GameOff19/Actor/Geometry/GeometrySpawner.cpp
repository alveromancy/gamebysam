// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometrySpawner.h"

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
	
}

void AGeometrySpawner::CubeDestroyed(TSubclassOf<class AGeometryClass>)
{

}


void AGeometrySpawner::SpawnCube(TSubclassOf<class AGeometryClass>)
{

}