// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "GeometryClass.generated.h"


UENUM(BlueprintType)
enum class EGeometryMaterial : uint8
{
	STONE UMETA(DisplayName = "Stone"),
	METAL UMETA(DisplayName = "Metal"),
	PLASTIC UMETA(DisplayName = "Plastic"),
	DARK_MATTER UMETA(DisplayName = "Dark Matter"),
	CRYSTAL UMETA(DisplayName = "Crystal")
};

UENUM(BlueprintType)
enum class EGeometryShape : uint8
{
	CONE_CAPPED UMETA(DisplayName = "Conic Frustum"),
	CONE UMETA(DisplayName = "Cone"),
	PENTAGON UMETA(DisplayName = "Pentagon Frsutum"),
	TETHAEDRON UMETA(DisplayName = "Tethaedron"),
	CUBE UMETA(DisplayName = "Cube"),
	SPHERE UMETA(DisplayName = "Sphere")
};

UENUM(BlueprintType)
enum class EGeometryElectricty : uint8
{
	CONDUCT UMETA(DisplayName = "Conducts Electricty"),
	NO_CONDUCT UMETA(DisplayName = "No Conducts Electricty"),
	ABSORB UMETA(DisplayName = "Absorbs Electricty")
};

UENUM(BlueprintType)
enum class EGeometryLight : uint8
{
	REFLECT UMETA(DisplayName = "Reflect light"),
	NO_REFLECT UMETA(DisplayName = "No Reflect light"),
	ABSORB UMETA(DisplayName = "Absorbs light")
};





UCLASS()
class GAMEOFF19_API AGeometryClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeometryClass();



	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//Getters
	UFUNCTION(BlueprintCallable)
		float GetWeight()const { return Weight;}

	UFUNCTION(BlueprintCallable)
		EGeometryMaterial GetMaterial()const { return Material; }

	UFUNCTION(BlueprintCallable)
		EGeometryLight GetLightBehaviour()const { return MaterialLight; }

	UFUNCTION(BlueprintCallable)
		EGeometryElectricty GetElectricityBehaviour()const { return MaterialElectricity; }

	//Call this function when you want to destroy the cube 
	UFUNCTION(BlueprintCallable)
		void DestroyCube(); 

	UFUNCTION(BlueprintImplementableEvent)
		void OnDestroyCube();


	void Internal_SetStatus(bool bIsAlive); 
	void Internal_SetSpawner(class AGeometrySpawner * SpawnActor);
	void Internal_ApplyImpulse(const FVector & Impulse); 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


protected: 

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Mesh")
		class UStaticMeshComponent * SM_Mesh;

	//Weight of the cube
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Properties")
		float Weight;
	//Reference to the spawner actor
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Spawner")
		class AGeometrySpawner * Spawner; 
	//Material 
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly,  Category = "Properties")
		EGeometryMaterial Material;
	//Behaviour with electricity
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly,  Category = "Properties")
		EGeometryElectricty MaterialElectricity;
	//Behaviour with light
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly,  Category = "Properties")
		EGeometryLight MaterialLight;

	//Can this Cube respawn? 
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Spawner")
		bool bCanRespawn = true; 

};


