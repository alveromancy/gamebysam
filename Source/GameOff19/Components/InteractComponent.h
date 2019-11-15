#pragma once

#include "Components/SceneComponent.h"
#include "Enums/InteractEnums.h"
#include "InteractComponent.generated.h"

UCLASS(BlueprintType, meta = (BlueprintSpawnableComponent))
class GAMEOFF19_API UInteractComponent : public USceneComponent {
	GENERATED_BODY()

public:
	UInteractComponent();

public:
	/*Call to interact with IInteractable. Retursn whether interaction is successful.*/
	UFUNCTION(BlueprintCallable, Category = Interact)
		bool Interact();

public:
	/*Type of interaction for currentInteractable*/
	UPROPERTY(BlueprintReadOnly, Category = Interact)
		EInteractType interactType;
	/*Interaction trace channel*/
	UPROPERTY(EditDefaultsOnly, meta=(DisplayAfter="distance"), Category = Interact)
		TEnumAsByte<ETraceTypeQuery> interactChannel;
	/*Current interacting object.*/
	UPROPERTY(BlueprintReadOnly, Category = Interact)
		AActor* currentInteractable;
	/*The offset of interact socket*/
	UPROPERTY(EditDefaultsOnly, Category = Interact)
		FVector offset;
	/*Interaction distance*/
	UPROPERTY(EditDefaultsOnly, Category = Interact)
		float distance;
};