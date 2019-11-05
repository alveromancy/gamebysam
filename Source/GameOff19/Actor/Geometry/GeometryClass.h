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
	METAL UMETA(DisplayName = "Meta"),
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
	Sphere UMETA(DisplayName = "Sphere")
};



USTRUCT(BlueprintType)
struct FGoemtryProperty : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EGeometryMaterial Material; 

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Light Reflection", UIMin = 0, UIMax = 100, ClampMin = 0, ClampMax = 100))
		int32 weight; 
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Light Reflection", UIMin = 0, UIMax = 100, ClampMin = 0, ClampMax = 100))
		int32 LightReflection;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Energy Conductivity",UIMin = 0, UIMax = 100, ClampMin = 0, ClampMax =100))
		int32 Conductivity;
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



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private: 
	UFUNCTION(BlueprintType)
		void CollisionHandle(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


protected: 

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Mesh")
		class UStaticMeshComponent * SM_Mesh;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Mesh")
		class UCapsuleComponent * CC_Collider;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Gameplay | Debug", meta = (DisplayName = "Ray reference"))
		class ALightRay * ARay; 

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Geometry Properties")
		EGeometryMaterial Material; 


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Geometry Properties")
		int32 Weight = 50; 

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Geometry Properties", meta = (DisplayName = "Reflection"))
		int32 LightReflection = 0.5; 

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Geometry Properties")
		int32 Conductivity = 0.5; 

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Gameplay", meta =(DisplayName = "Energy Level"))
		float EnergyAbsorbed = 0;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Gameplay | Debug", meta = (DisplayName = "Conducting Energy"))
		bool bIsConductingEnergy = false;






};
