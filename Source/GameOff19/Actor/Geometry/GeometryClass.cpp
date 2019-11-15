// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryClass.h"
#include "Components/StaticMeshComponent.h"
#include "GameOff19/Actor/Geometry/GeometrySpawner.h"
#include "Components/CapsuleComponent.h"





// Sets default values
AGeometryClass::AGeometryClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SM_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh"); 
	RootComponent = SM_Mesh; 
	SM_Mesh->SetCollisionProfileName("Cube");
	SM_Mesh->SetSimulatePhysics(true);
		
}

void AGeometryClass::Interact_Implementation(EInteractType& interactType)
{
	//Output
	interactType = EInteractType::PickUp;

	//Update control variable
	bIsGrabbed = !bIsGrabbed;
	//Update collision and physics
	SM_Mesh->SetPhysicsLinearVelocity(FVector(0)); 
	SM_Mesh->SetPhysicsAngularVelocity(FVector(0));
	SM_Mesh->SetSimulatePhysics( !bIsGrabbed);
	
	(bIsGrabbed) ? SM_Mesh->SetCollisionProfileName("GrabbedCube") : SM_Mesh->SetCollisionProfileName("Cube");
	
}


void AGeometryClass::Internal_SetSpawner(class AGeometrySpawner * SpawnActor)
{
	Spawner = SpawnActor;
}

void AGeometryClass::Internal_SetStatus(bool bIsAlive)
{
	
	SetActorEnableCollision(bIsAlive);

	SetActorHiddenInGame(!bIsAlive);

	SM_Mesh->SetSimulatePhysics(bIsAlive);

}


void AGeometryClass::Internal_ApplyImpulse(const FVector & Impulse)
{
	SM_Mesh->AddImpulse(Impulse);
}

// Called when the game starts or when spawned
void AGeometryClass::BeginPlay()
{
	Super::BeginPlay();
	SM_Mesh->SetMassOverrideInKg(NAME_None, Weight * 100, true);
}

// Called every frame
void AGeometryClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGeometryClass::DestroyCube()
{
	OnDestroyCube();

	if (Spawner && bCanRespawn)
		Spawner->CubeDestroyed(this);
	else
		Destroy(); 
}

