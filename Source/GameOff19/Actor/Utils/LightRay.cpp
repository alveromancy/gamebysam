// Fill out your copyright notice in the Description page of Project Settings.


#include "LightRay.h"

// Sets default values
ALightRay::ALightRay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALightRay::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightRay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

