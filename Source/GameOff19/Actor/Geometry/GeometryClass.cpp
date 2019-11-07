// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryClass.h"
#include "Components/StaticMeshComponent.h"
#include "GameOff19/Actor/Geometry/GeometrySpawner.h"
#include "Components/CapsuleComponent.h"



FGeometryMaterialProperties::FGeometryMaterialProperties()
{
	Weight = 5.0f; 
}

FGeometryMaterialProperties::FGeometryMaterialProperties(const AGeometryClass * Cube)
{
	if (Cube)
	{
		Weight = Cube->GetWeight();
		Material = Cube->GetMaterial();
		MaterialLight = Cube->GetLightBehaviour();
		MaterialElectricity = Cube->GetElectricityBehaviour();
	}
	else
		Weight = 5.0f; 
}


// Sets default values
AGeometryClass::AGeometryClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SM_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh"); 
	RootComponent = SM_Mesh; 
	SM_Mesh->SetCollisionProfileName("PhysicsActor");
	SM_Mesh->SetSimulatePhysics(true);
	
}




// Called when the game starts or when spawned
void AGeometryClass::BeginPlay()
{
	Super::BeginPlay();
	SM_Mesh->SetMassOverrideInKg(NAME_None, Weight, true);
}

// Called every frame
void AGeometryClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGeometryClass::BeginDestroy()
{
	Super::BeginDestroy();
	if (Spawner)
		Spawner->CubeDestroyed(this,bCanRespawn);
}

//INTERNAL FUNCTIONS

void AGeometryClass::Internal_BuildFromParams(const FGeometryMaterialProperties & Properties)
{
	Material = Properties.Material;
	MaterialLight = Properties.MaterialLight;
	MaterialElectricity = Properties.MaterialElectricity;
	Weight = Properties.Weight;

	Internal_SetVisualsFromDataTable();
}


void AGeometryClass::Internal_SetVisualsFromDataTable()
{
	if (GeometryTableReference)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AGeometryClass::Internal_SetVisualsFromDataTable:: DataTable is not properly set")); 
	}
}