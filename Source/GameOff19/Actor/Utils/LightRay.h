// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightRay.generated.h"

UENUM(BlueprintType)
enum class ERayCollision : uint8
{
	IGNORE UMETA(DisplayName ="Rays Ignores"),
	MERGE UMETA(DisplayName ="Rays Merges")
};

UCLASS()
class GAMEOFF19_API ALightRay : public AActor
{
	GENERATED_BODY()


public: /*Editor functions */

	//Function fired when the actor is created
	virtual void PostActorCreated()override;

#if WITH_EDITOR
	//Function fired when actor is moved while in editor.
	virtual void PostEditMove(bool bFinished) override;
#endif

public:	/*Runtime Functions */
	// Sets default values for this actor's properties
	ALightRay();
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FHitResult RecalculateRayLenght();

private: 
	bool RayTrace(FHitResult & OutHit);

/*Atributes*/
protected: 

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(DisplayName = "Mesh"))
		class UStaticMeshComponent * SM_Mesh; 

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Ray Properties")
		ERayCollision CollisionType;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Ray Properties | Debug", meta=(DisplayName = "Initial Scale"))
		FVector OriginalScaleFactor; 
private: 

	const int32 LIGHT_MAXIMUM_DISTANCE = 50000;

};
