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
	UFUNCTION(BlueprintCallable)
	void CubeDestroyed(class AGeometryClass * destroyed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private: 
	
	void Internal_Init();

	void SpawnCube(class AGeometryClass * CubeToSpawn);
	void TimerEvent();
protected: 


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Spawner")
		bool bCanSpawn = true;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Spawner")
		float TimeBetweenSpawn = 1.5f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Spawner", meta = (DisplayName = "Cube Impulse"))
		float Impulse = 2000.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Spawner")
		TArray< TSubclassOf<class AGeometryClass> > CubesToSpawn; 

	UPROPERTY(VisibleAnywhere,Category = "Debug")
	TArray< class AGeometryClass *> SpawnQueue; 
	FTimerHandle SpawnTimer; 
	

	

};
