// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightRay.generated.h"

USTRUCT(BlueprintType)
struct FReflectionData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		FVector ImpactPoint; 
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		FVector Normal; 
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		FVector ReflectedDirection;

	FReflectionData()
	{

	}

	FReflectionData(FVector Impact, FVector Normal)
	: ImpactPoint(Impact),Normal(Normal)
	{}

	bool operator== (const FReflectionData & B)
	{
		return ImpactPoint.Equals(B.ImpactPoint) && Normal.Equals(B.Normal);
	}

	bool operator!=(const FReflectionData & B)
	{
		return !ImpactPoint.Equals(B.ImpactPoint) || !Normal.Equals(B.Normal);
	}

	void Debug(UWorld * World);

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

	virtual void PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent) override; 

#endif

public:	/*Runtime Functions */
	// Sets default values for this actor's properties
	ALightRay();
	virtual void Tick(float DeltaTime) override;

	virtual void BeginDestroy()override; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FHitResult RecalculateRayLenght();

	void SetRelfectionIndex(int32 index) { ReflectionIndex = index; }

private: 
	bool RayTrace(FHitResult & OutHit);

	void ReflectLight(const FVector & ImpactPoint, const FVector & Normal);

	ALightRay * SpawnReflectedLight(const FVector & ImpactPoint, const FVector & Direction); 

/*Atributes*/
protected: 

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(DisplayName = "Mesh"))
		class UStaticMeshComponent * SM_Mesh; 

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ray Properties")
		float RayRadius = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ray Properties | Reflection")
		int32 ReflectionIndex = 0;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Ray Properties | Reflection")
		FReflectionData CurrentReflection;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Ray Properties | Reflection")
		ALightRay * ReflectedRay;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Ray Properties | Debug", meta = (DisplayName = "Initial Scale"))
		FVector OriginalScaleFactor;




private: 

	static const float RADIUS_CONSTANT; 
	static const int32 LIGHT_MAXIMUM_DISTANCE;
	static const int32 MAX_REFLECTIONS;

};
