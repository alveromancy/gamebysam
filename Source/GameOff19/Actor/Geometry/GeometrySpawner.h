// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeometrySpawner.generated.h"

UCLASS()
class GAMEOFF19_API AGeometrySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeometrySpawner();

	void CubeDestroyed(TSubclassOf<class AGeometryClass>);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private: 

	void SpawnCube(TSubclassOf<class AGeometryClass>);
protected: 

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Spawner")
		TArray< TSubclassOf<class AGeometryClass> > CubesToSpawn; 


};
