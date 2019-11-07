// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveElectricActor.h"


void  UInteractiveElectricActor::InteractiveActivate()
{
	bIsActivated = true;
	PropagateElectricity();
	OnActivate.Broadcast(bIsElectrified);
}

void UInteractiveElectricActor::InteractiveDeactivate()
{
	bIsActivated = false;
	PropagateElectricity();
	OnDeactivate.Broadcast(bIsElectrified);
}


void UInteractiveElectricActor::PropagateElectricity()
{
	if (ElectricComponentReference)
	{
		if (bIsElectrified && bIsActivated)
			ElectricComponentReference->TurnOnElectricity();
		else
			ElectricComponentReference->TurnOffElectricity();
	}
}