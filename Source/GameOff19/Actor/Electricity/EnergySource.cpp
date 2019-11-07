// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergySource.h"
#include "Components/StaticMeshComponent.h"
#include "GameOff19/Actor/Utils/ElectricityActor.h"

// Sets default values
AEnergySource::AEnergySource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SM_PrimaryMesh = CreateDefaultSubobject<UStaticMeshComponent>("PrimaryMesh"); 
	RootComponent = SM_PrimaryMesh; 

	EA_Electricity = CreateDefaultSubobject<UElectricityActor>("Electricity"); 
	EA_Electricity->SetPropagateFlag(true); 

}

// Called when the game starts or when spawned
void AEnergySource::BeginPlay()
{
	Super::BeginPlay();
	EA_Electricity->TurnOnElectricity();
}



void AEnergySource::ActivateSource()
{
	bIsActivated = true; 
	OnSourceActivate(); 
	EA_Electricity->TurnOnElectricity();
}

void AEnergySource::DeactivateSource()
{
	bIsActivated = false;
	OnSourceDeactivate();
	EA_Electricity->TurnOffElectricity();
}

