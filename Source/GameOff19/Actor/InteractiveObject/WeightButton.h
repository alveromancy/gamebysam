// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeightButton.generated.h"


UCLASS()
class GAMEOFF19_API AWeightButton : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	AWeightButton();

	UFUNCTION(BlueprintCallable)
		bool IsButtonActive()const { return bIsActivated; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
		void ObjectDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void ObjectLost(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Activate();
	UFUNCTION(BlueprintImplementableEvent)
		void OnButtonActivate();
	void Deactivate();
	UFUNCTION(BlueprintImplementableEvent)
		void OnButtonDeactivate();


protected: 

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta =(AllowPrivateAcces = "True"))
		class UBoxComponent*  BC_Collider;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAcces = "True"))
		class UStaticMeshComponent* SM_Mesh; 

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Activation")
		bool bIsActivated = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Activation")
		bool bCanPlayerActivate = false; 

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Activation")
		float GoalWeight = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Activation")
		float CurrentWeight = 0; 




};
