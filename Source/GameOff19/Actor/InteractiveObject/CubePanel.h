// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameOff19/Actor/Geometry/GeometryClass.h"
#include "CubePanel.generated.h"

UCLASS()
class GAMEOFF19_API AcubePanel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AcubePanel();

	UFUNCTION(BlueprintCallable)
		bool IsActivated()const { return bIsActivated; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	void Activate();
	UFUNCTION(BlueprintImplementableEvent)
		void OnPanelActivate(); 

	void Deactivate();
	UFUNCTION(BlueprintImplementableEvent)
		void OnPanelDeactivate();

	UFUNCTION()
		void ObjectDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void ObjectLost(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected: 

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAcces = "True"))
		class UBoxComponent*  BC_Collider;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAcces = "True"))
		class UStaticMeshComponent* SM_Mesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Activation | Debug")
		AGeometryClass * CubeRef; 

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Activation | Debug")
		bool bIsActivated = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Activation")
		bool bCanPlayerActivate = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Activation")
		TSet<EGeometryMaterial> AcceptedMaterials; 


};
