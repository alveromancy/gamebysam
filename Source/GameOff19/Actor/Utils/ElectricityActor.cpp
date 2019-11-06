// Fill out your copyright notice in the Description page of Project Settings.


#include "ElectricityActor.h"
#include "GameFramework/Actor.h"


// Sets default values
UElectricityActor::UElectricityActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void UElectricityActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (ActorToPlugg)
	{
		UActorComponent * Component = ActorToPlugg->GetComponentByClass(UElectricityActor::StaticClass());
		ElectricComponentReference = Cast< UElectricityActor>(Component);
	}

}



void UElectricityActor::TurnOffElectricity()
{
	bIsElectrified = false; 
	OnDeElectrified.Broadcast();
	PropagateElectricity();
 }


void UElectricityActor::TurnOnElectricity()
{
	bIsElectrified = true; 
	OnElectrified.Broadcast();
	PropagateElectricity();
}

void UElectricityActor::SetPropagateFlag(bool bCanPropagateElectricity)
{
	bCanPropagate = bCanPropagateElectricity;
}


bool UElectricityActor::NewPlug(UElectricityActor*  NewPluggedActor)
{
	if (ElectricComponentReference)
		ElectricComponentReference->TurnOffElectricity();

	ElectricComponentReference = NewPluggedActor;
	PropagateElectricity();

	return bIsElectrified;
}

void UElectricityActor::PropagateElectricity()
{
	if (ElectricComponentReference)
	{
		if (bIsElectrified && bCanPropagate)
			ElectricComponentReference->TurnOnElectricity();
		else if (!bIsElectrified)
			ElectricComponentReference->TurnOffElectricity();
	}
}

