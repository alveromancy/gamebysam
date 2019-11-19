#include "InteractComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Interfaces/IInteractable.h"
#include "GameOff19Character.h"
#include "Engine/World.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"

UInteractComponent::UInteractComponent() {

}

bool UInteractComponent::Interact() {

	bool isInteract = false;
	if (currentInteractable == nullptr) {

		//Grab camera component
		AGameOff19Character* character = Cast<AGameOff19Character>(GetOwner());
		ensureMsgf(character != nullptr, TEXT("Character can't be found!"));
		UCameraComponent* camera = character->GetFirstPersonCameraComponent();
		ensureMsgf(camera != nullptr, TEXT("Camera can't be found!"));

		FHitResult hitResult;
		FVector tracePos = camera->GetComponentLocation() + offset;
		FVector traceEnd = tracePos + camera->GetForwardVector() * distance;
		ECollisionChannel channel = UEngineTypes::ConvertToCollisionChannel(interactChannel);
		DrawDebugLine(GetWorld(), tracePos, traceEnd, FColor::Red, false, 5.0f, 0, 0.5f);
		if (GetWorld()->LineTraceSingleByChannel(hitResult, tracePos, traceEnd, channel)) {
			if (hitResult.Actor.IsValid()) {
				if (hitResult.Actor.Get()->GetClass()->ImplementsInterface(UIInteractable::StaticClass())) {
					currentInteractable = hitResult.Actor.Get();
					IIInteractable::Execute_Interact(currentInteractable, interactType);
					if (interactType == EInteractType::PickUp) {
						currentInteractable->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					}
					else {
						currentInteractable = nullptr;
					}
					isInteract = true;
				}
			}
		}
	}
	else {
		currentInteractable->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		IIInteractable::Execute_Interact(currentInteractable, interactType);
		currentInteractable = nullptr;
		isInteract = false;
	}
	return isInteract;
}