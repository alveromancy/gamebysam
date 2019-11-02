// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GenericBarComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEmptyAmmount); 

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEOFF19_API UGenericBarComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGenericBarComponent();

	/**
		Adds some amount of quantity to the current value. 
		@param Quantity amount to increase
		@return Current value after the increse
	*/
	UFUNCTION(BlueprintCallable)
	virtual float Add(float Quantity); 

	/**
		Withdraws some amount of quantity to the current value.
		@param Quantity amount to decrease
		@return Current value after the decrease
	*/
	UFUNCTION(BlueprintCallable)
	virtual float Withdraw(float Quantity); 

	/**
		Get the current Amount 
		@return Current amount
	*/
	UFUNCTION(BlueprintPure)
		float GetAmmount()const; 


	/**
	Get the current relative Amount (between 0 - 1) 
	@return Current relative amount
	*/
	UFUNCTION(BlueprintPure)
		float GetRelativeAmmount()const;

	/**
		Get the maximum Amount
		@return maximum amount
	*/
	UFUNCTION(BlueprintPure)
		float GetMaximumAmount()const; 


	/**
		Set the maximum Amount
		@param new maximum amount
		@param Should refill the bar
	*/
	UFUNCTION(BlueprintCallable)
		void SetMaximum(float max, bool bRefill = false); 

	/**
		Sets the current ammount to the maximum
	*/
	UFUNCTION(BlueprintCallable)
		void Refill(); 



protected: 

	//ATRIBUTES 

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta =(DisplayName = "Maximum Value"))
		float MaxAmmount = 100; 

	UPROPERTY(BlueprintReadWrite, EditAnywhere , meta = (DisplayName = "Current Value"))
		float CurrentAmmount = 100; 


	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "HUD Widget"))
		TSubclassOf< class UGenericBar > WidgetReference; 


protected: 

	//DELEGATES
	UPROPERTY(BlueprintAssignable)
	FEmptyAmmount OnRunnedOut;
		
};
