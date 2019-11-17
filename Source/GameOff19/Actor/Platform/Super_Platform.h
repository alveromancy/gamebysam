// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Super_Platform.generated.h"

UENUM(BlueprintType)
enum class EPlatformMovement : uint8
{
	ONE_WAY UMETA(DisplayName = "One Way"),
	MULTIPLE_WAY UMETA(DisplayName = "Multiple Way"),
	LOOP UMETA(DisplayName = "Loop")
};


UENUM(BlueprintType)
enum class EPlatformActivation : uint8
{
	AUTO UMETA(DisplayName = "Automatic"), 
	PLAYER_STEP_UP UMETA(DisplayName = "Player Set Up"), 
	REMOTE_ACTIVATION UMETA(DisplayName = "Remote")
};

UENUM(BlueprintType)
enum class EPlatformDeactivation : uint8
{
	NO_DEACTIVATION UMETA(DisplayName = "Always Activated"), 
	TIMER UMETA(DisplayName = "Timer"), 
	PLAYER_STEP_DOWN UMETA(DisplayName = "Player leave"), 
	REMOTE_DEACTIVATION UMETA(DisplayName = "Remote")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDetected); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerUndetected); 


UCLASS()
class GAMEOFF19_API ASuper_Platform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASuper_Platform();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Actiavtes the platform 
	UFUNCTION(BlueprintCallable)
	void ActivatePlatform(); 

	/**
	* Stops the platform, if bShouldReset is set, will return to it's initial state. 
	*/
	UFUNCTION(BlueprintCallable)
	void DeactivatePlatform();

	UFUNCTION(BlueprintCallable)
	void Reset();


#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent)override;
#endif

protected: 

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private: 

	void MovePlatform();
	void RotatePlatform();
	void EdgeReached();
	void DisablePlatform();

	UFUNCTION()
	void TimeOut();

	UFUNCTION()
	void PlayerDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void PlayerDetectionLost(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


protected: 

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class USplineComponent * S_Path; 

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UStaticMeshComponent * SM_Mesh; 

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class USphereComponent * SC_Collider;	

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Platform | Config")
		EPlatformMovement Movement;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Platform | Config")
		EPlatformActivation Activation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Platform | Config")
		EPlatformDeactivation Deactivation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Platform | Path", meta = (DisplayName = "Waiting time lap", EditCondition = "Movement == EPlatformMovement::LOOP"))
		float LapTimeWait;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Platform | Config", meta=(DisplayName = "Return when deactivated"))
		bool bShouldReset; 

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Platform | Config")
		bool bShouldRotate;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Platform | Config", meta = (DisplayName = "Time Platform is activated" , EditCondition = "Deactivation == EPlatformDeactivation::TIMER"))
		float TimerToDeactivate; 
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Debug")
		bool bIsActivated;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Debug")
		bool bWantsToDeactivate;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Debug")
		bool bIsReverse;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Platform | Path", meta=(DisplayName = "Travel Time", ClampMin = 0.1))
		float Time = 1; 

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Platform | Path", meta=(DisplayName = "Starting Point", UIMin = 0, UIMax = 1, ClampMin = 0, ClampMax = 1))
		float StartingPoint = 0; 

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Debug")
		float CurrentTime = 0;


	FTimerHandle TimerHandle; 
	bool bTimeGone = false; 

	//Delegates 
	UPROPERTY(BlueprintAssignable)
	FPlayerDetected OnPlayerDetected;

	UPROPERTY(BlueprintAssignable)
	FPlayerUndetected OnPlyaerUndetected; 
};
