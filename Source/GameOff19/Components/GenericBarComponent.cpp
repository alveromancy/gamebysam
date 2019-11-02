// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericBarComponent.h"
#include "GameOff19/Widgets/GenericBar.h"

// Sets default values for this component's properties
UGenericBarComponent::UGenericBarComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


float UGenericBarComponent::Add(float Quantity)
{
	CurrentAmmount = (CurrentAmmount + Quantity > MaxAmmount) ? MaxAmmount : CurrentAmmount + Quantity; 

	if (WidgetReference)
		WidgetReference->GetDefaultObject<UGenericBar>()->Update(CurrentAmmount);

	return CurrentAmmount;
}

float UGenericBarComponent::Withdraw(float Quantity)
{
	if (CurrentAmmount > 0)
	{
		CurrentAmmount = (CurrentAmmount - Quantity < 0) ? 0 : CurrentAmmount - Quantity;

		if (CurrentAmmount == 0)
			OnRunnedOut.Broadcast();

		if (WidgetReference)
			WidgetReference->GetDefaultObject<UGenericBar>()->Update(CurrentAmmount);
	}
	
	return CurrentAmmount;
}

float UGenericBarComponent::GetAmmount()const
{
	return CurrentAmmount;
}


float UGenericBarComponent::GetRelativeAmmount()const
{
	return CurrentAmmount / MaxAmmount; 
}



float UGenericBarComponent::GetMaximumAmount()const
{
	return MaxAmmount;
}


void UGenericBarComponent::SetMaximum(float max, bool bRefill)
{
	MaxAmmount = max; 
	if (CurrentAmmount > MaxAmmount || bRefill)
		CurrentAmmount = MaxAmmount; 

}

void UGenericBarComponent::Refill()
{
	CurrentAmmount = MaxAmmount;
}
