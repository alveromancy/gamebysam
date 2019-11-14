// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Interfaces/IInteractable.h"
#include "SwitchButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSwitchSignature);

UCLASS(BlueprintType, Blueprintable)
class GAMEOFF19_API ASwitchButton : public AActor, public IIInteractable {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASwitchButton();
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/*Call to toggle switch's state.*/
	UFUNCTION(BlueprintCallable, Category = Switch)
		void ToggleState();
	/*Call to change switch's state to desired state.*/
	UFUNCTION(BlueprintCallable, Category = Switch)
		void SwitchStateTo(bool desiredState);
	/*Call to start switch's timer.*/
	UFUNCTION(BlueprintCallable, Category = Switch)
		void StartTimer();
	/*Call to toggle switch's locked state.*/
	UFUNCTION(BlueprintCallable, Category = Switch)
		void ChangeLockState(bool state);
	//Events
	/*Calls whenever switch state gets toggled.*/
	UPROPERTY(BlueprintAssignable, Category = Switch)
		FSwitchSignature OnToggle;
	/*Calls whenever switch state gets changed.(Not available for toggle mode)*/
	UPROPERTY(BlueprintAssignable, Category = Switch)
		FSwitchSignature OnStateChange;
	/*Calls whenever switch gets locked.*/
	UPROPERTY(BlueprintAssignable, Category = Switch)
		FSwitchSignature OnLocked;
	/*Calls whenever switch gets unlocked.*/
	UPROPERTY(BlueprintAssignable, Category = Switch)
		FSwitchSignature OnUnlocked;
	/*Calls whenever timer starts.*/
	UPROPERTY(BlueprintAssignable, Category = Switch)
		FSwitchSignature OnTimerStart;
	/*Calls whenever timer finishes.*/
	UPROPERTY(BlueprintAssignable, Category = Switch)
		FSwitchSignature OnTimerFinished;
	//Interaction
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Interactable)
		void Interact(EInteractType& interactType);
	void Interact_Implementation(EInteractType& interactType);

private:
	UFUNCTION()
		void TimerFinished();

public:
	/*Is switch locked?*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Switch)
		bool isLocked;
	/*Initial state of switch*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (EditCondition = "isToggle==false"), Category = Switch)
		bool initialState;
	/*Result state of switch*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Switch)
		bool resultState;
	/*Set switch to toggle mode*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Switch)
		bool isToggle;
	/*Set switch with timer*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Switch)
		bool isTimed;
	/*How long will the timer be?*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (EditCondition = "isTimed==true"), Category = Switch)
		float countdownTime;

protected:
	/*Current switch's state*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Switch)
		bool state;
	FTimerHandle timerHandler;

private:
	/*Switch Mesh*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Interactable)
		class USkeletalMeshComponent* mesh;
	/*Switch's Interact Component*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Interactable)
		class UAORComponent* AORComponent;
};
