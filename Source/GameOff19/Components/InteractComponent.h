#pragma once

#include "Components/ActorComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "Interfaces/IInteractable.h"
#include "Enums/InteractEnums.h"
#include "InteractComponent.generated.h"

UCLASS(BlueprintType, meta = (BlueprintSpawnableComponent))
class GAMEOFF19_API UInteractComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UInteractComponent();

public:
	/*Call to interact with IInteractable. Retursn whether interaction is successful.*/
	UFUNCTION(BlueprintCallable, Category = Interact)
		bool Interact();
	UFUNCTION(BlueprintCallable, Category = Interact)
		FVector GetInteractPoint(const EHandType hand);

public:
	/*Socket that interacted object will be attached to*/
	UPROPERTY(EditDefaultsOnly, Category = Interact)
		FName interactSocketName;
	/*The offset for interaction*/
	UPROPERTY(EditDefaultsOnly, Category = Interact)
		FVector offset;
	/*Bone name of left hand interaction trace position*/
	UPROPERTY(EditDefaultsOnly, Category = Interact)
		FName leftBoneName;
	/*Bone name of left hand interaction trace position*/
	UPROPERTY(EditDefaultsOnly, Category = Interact)
		FName rightBoneName;
	/*Interaction distance*/
	UPROPERTY(EditDefaultsOnly, Category = Interact)
		float distance;
	/*Interaction trace channel*/
	UPROPERTY(EditDefaultsOnly, Category = Interact)
		TEnumAsByte<ETraceTypeQuery> interactChannel;
	UPROPERTY(BlueprintReadOnly, Category = Interact)
		AActor* currentInteractable;
	UPROPERTY(BlueprintReadOnly, Category = Interact)
		EInteractType interactType;
	UPROPERTY(BlueprintReadOnly, Category = Interact)
		EHandIKType handIKType;
};