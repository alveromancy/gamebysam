// Fill out your copyright notice in the Description page of Project Settings.


#include "CubePanel.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AcubePanel::AcubePanel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BC_Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	RootComponent = BC_Collider;

	BC_Collider->OnComponentBeginOverlap.AddDynamic(this, &AcubePanel::ObjectDetected);
	BC_Collider->OnComponentEndOverlap.AddDynamic(this, &AcubePanel::ObjectLost);

	SM_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SM_Mesh->SetupAttachment(BC_Collider);
	SM_Mesh->SetCollisionProfileName("NoCollision");
}

// Called when the game starts or when spawned
void AcubePanel::BeginPlay()
{
	Super::BeginPlay();
	
}

void AcubePanel::Activate()
{
	bIsActivated = true; 
	OnPanelActivate();
}

void AcubePanel::Deactivate()
{
	bIsActivated = false; 
	OnPanelDeactivate();
}

void AcubePanel::ObjectDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!CubeRef) //Do nothing if we already have one 
	{
		AGeometryClass * Cube = Cast<AGeometryClass>(OtherActor);
		if (Cube && AcceptedMaterials.Find(Cube->GetMaterial()))
		{
			CubeRef = Cube;
			Activate();
		}
	}
	
}




void AcubePanel::ObjectLost(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == CubeRef)
	{
		CubeRef = nullptr; 
		Deactivate();
	}
}


