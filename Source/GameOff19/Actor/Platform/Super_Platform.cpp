// Fill out your copyright notice in the Description page of Project Settings.


#include "Super_Platform.h"

// Sets default values
ASuper_Platform::ASuper_Platform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASuper_Platform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASuper_Platform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

