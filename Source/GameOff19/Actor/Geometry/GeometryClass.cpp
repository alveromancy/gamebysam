// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryClass.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AGeometryClass::AGeometryClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SM_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh"); 
	RootComponent = SM_Mesh; 
	SM_Mesh->SetCollisionProfileName("NoCollision");
	//SM_Mesh->OnComponentHit.AddDynamic(this, &AGeometryClass::CollisionHandle);


}

// Called when the game starts or when spawned
void AGeometryClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGeometryClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



