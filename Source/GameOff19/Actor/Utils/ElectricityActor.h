// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ElectricityActor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnElectrified); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeelectrified);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAMEOFF19_API UElectricityActor : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UElectricityActor();

	UFUNCTION(BlueprintCallable)
		virtual bool NewPlug(UElectricityActor* NewPluggedActor);

	/**
	* 	Turns off the electricity for this component. Sets bIsElectrified to false, Calls OnDeelectrified event and tries to propoagate the "non-electricity" to the next actor.
	*/
	UFUNCTION(BlueprintCallable)
		virtual void TurnOffElectricity(); 

	/**
	* Turns on the electricity for this component. Sets bIsElectrified to true, Calls OnElectrified event and tries to propoagate the electricity to the next actor.
	**/
	UFUNCTION(BlueprintCallable)
		virtual void TurnOnElectricity();

	/**
	* Set if the compoment can propagate when is electrified
	*/
	UFUNCTION(BlueprintCallable)
		void SetPropagateFlag(bool bCanPropagateElectricity); 


	UFUNCTION(BlueprintCallable)
		bool GetPropagateFlag()const { return bCanPropagate; }

	UFUNCTION(BlueprintCallable)
		bool IsElectrified()const { return bIsElectrified;  }

	UFUNCTION(BlueprintCallable)
		bool CanPropagate()const { return (bIsElectrified) ? bCanPropagate : true;  }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**Propagates the electricity to the next Plugged actor if it's possible
	* Note: If component is electrified only propagates if SetPropagate is true. 
	* Note: If component is not electrified, it propagates always. 
	*/
	UFUNCTION(BlueprintCallable)
	virtual void PropagateElectricity();


protected: 

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Plugged")
		class AActor * ActorToPlugg; 

	UElectricityActor* ElectricComponentReference;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Properties")
		bool bIsElectrified; 
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Properties")
		bool bCanPropagate = true; 

	UPROPERTY(BlueprintAssignable)
		FOnElectrified OnElectrified; 

	UPROPERTY(BlueprintAssignable)
		FOnDeelectrified OnDeElectrified;

};
