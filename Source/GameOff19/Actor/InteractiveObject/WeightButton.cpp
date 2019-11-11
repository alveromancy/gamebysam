// Fill out your copyright notice in the Description page of Project Settings.


#include "WeightButton.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameOff19/Actor/Geometry/GeometryClass.h"




// Sets default values for this component's properties
AWeightButton::AWeightButton()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = false;

	// ...

	BC_Collider = CreateDefaultSubobject<UBoxComponent>("Collider"); 
	RootComponent = BC_Collider;

	BC_Collider->OnComponentBeginOverlap.AddDynamic(this, &AWeightButton::ObjectDetected);
	BC_Collider->OnComponentEndOverlap.AddDynamic(this, &AWeightButton::ObjectLost);

	SM_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh"); 
	SM_Mesh->SetupAttachment(BC_Collider);
	SM_Mesh->SetCollisionProfileName("NoCollision");
}


// Called when the game starts
void AWeightButton::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



void AWeightButton::Activate()
{
	bIsActivated = true; 
	OnButtonActivate();
}
void AWeightButton::Deactivate()
{
	bIsActivated = false;
	OnButtonDeactivate();
}


void AWeightButton::ObjectDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACharacter>(OtherActor) && bCanPlayerActivate)
	{
		Activate(); 
	}
	else if(AGeometryClass * geo = Cast<AGeometryClass>(OtherActor))
	{
		CurrentWeight += geo->GetWeight();
		if (CurrentWeight >= GoalWeight && !bIsActivated)
			Activate();
	}

}



void AWeightButton::ObjectLost(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	 if (AGeometryClass * geo = Cast<AGeometryClass>(OtherActor))
	{
		CurrentWeight -= geo->GetWeight();
		if (CurrentWeight < GoalWeight && bIsActivated)
			Deactivate();
		
	}
	 else if(Cast<ACharacter>(OtherActor))
	 {
		 if (CurrentWeight < GoalWeight && bIsActivated)
			 Deactivate();
	 }


}
