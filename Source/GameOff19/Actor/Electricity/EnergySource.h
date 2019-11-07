// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnergySource.generated.h"

UCLASS()
class GAMEOFF19_API AEnergySource : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnergySource();

	UFUNCTION(BlueprintCallable)
		void ActivateSource(); 

	UFUNCTION(BlueprintCallable)
		void DeactivateSource();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION(BlueprintImplementableEvent)
		void OnSourceActivate(); 

	UFUNCTION(BlueprintImplementableEvent)
		void OnSourceDeactivate();
protected: 

	 UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Component")
		class UStaticMeshComponent * SM_PrimaryMesh; 

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Component")
		class UElectricityActor * EA_Electricity;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Properties")
		bool bIsActivated = true; 
};
