// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshSocket.h"
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
	//Events
	/*Called whenever switch state has been toggled.*/
	UPROPERTY(BlueprintAssignable, Category = Switch)
		FSwitchSignature OnToggle;
	/*Called whenever switch state has been changed.(Does not get called when switch state has been toggled.)*/
	UPROPERTY(BlueprintAssignable, Category = Switch)
		FSwitchSignature OnStateChange;
	UPROPERTY(BlueprintAssignable, Category = Switch)
		FSwitchSignature OnTimerStart;
	UPROPERTY(BlueprintAssignable, Category = Switch)
		FSwitchSignature OnTimerFinished;
	//Interaction
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Interactable)
		void Interact(EInteractType& interactType, EHandIKType& handIKType);
	virtual void Interact_Implementation(EInteractType& interactType, EHandIKType& handIKType) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Interactable)
		FVector GetLeftInteractPoint() const;
	virtual FVector GetLeftInteractPoint_Implementation() const override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Interactable)
		FVector GetRightInteractPoint() const;
	virtual FVector GetRightInteractPoint_Implementation() const override;

private:
	UFUNCTION()
		void TimerFinished();

public:
	UPROPERTY(EditAnywhere, meta = (EditCondition = "isToggle==false"), Category = Switch)
		bool desiredState;
	UPROPERTY(EditAnywhere, Category = Switch)
		bool isToggle;
	UPROPERTY(EditAnywhere, Category = Switch)
		bool hasTimer;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "hasTimer==true"), Category = Switch)
		float countdownTime;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "hasTimer==true"), Category = Switch)
		bool timeOutState;

	//Interaction
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Interactable)
		UStaticMeshComponent* mesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Interactable)
		FName leftHandSocket;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Interactable)
		FName rightHandSocket;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Switch)
		bool state;
	FTimerHandle timerHandler;
};
