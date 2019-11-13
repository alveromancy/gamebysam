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
		FHitResult hitResult;
		AGameOff19Character* character = Cast<AGameOff19Character>(GetOwner());
		ensureMsgf(character != nullptr, TEXT("Character can't be found!"));
		UCameraComponent* camera = character->GetFirstPersonCameraComponent();
		ensureMsgf(camera != nullptr, TEXT("Camera can't be found!"));
		FVector tracePos = camera->GetComponentLocation() + offset;
		FVector traceEnd = tracePos + camera->GetForwardVector() * distance;
		ECollisionChannel channel = UEngineTypes::ConvertToCollisionChannel(interactChannel);
		DrawDebugLine(GetWorld(), tracePos, traceEnd, FColor::Red, false, 5.0f, 0, 0.5f);
		if (GetWorld()->LineTraceSingleByChannel(hitResult, tracePos, traceEnd, channel))
		{
			if (hitResult.Actor.IsValid()) {
				currentInteractable = hitResult.Actor.Get();
				if (currentInteractable->GetClass()->ImplementsInterface(UIInteractable::StaticClass()))
				{
					IIInteractable::Execute_Interact(currentInteractable, interactType, handIKType);
					isInteract = true;
				}
			}
		}
	}
	else {
		currentInteractable->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		IIInteractable::Execute_Interact(currentInteractable, interactType, handIKType);
		currentInteractable = nullptr;
		isInteract = false;
	}
	return isInteract;
}

void UInteractComponent::AttachObject() {

	if (interactType == EInteractType::PickUp) {
		USkeletalMeshComponent* mesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
		if (mesh != nullptr) {
			if (ensureAlwaysMsgf(mesh->DoesSocketExist(interactSocketName), TEXT("Socket is invalid!")))
			{
				currentInteractable->AttachToComponent(mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, interactSocketName);
			}
		}
	}
}

FVector UInteractComponent::GetInteractPoint(const EHandType hand) {
	
	FVector interactPoint;
	if (currentInteractable != nullptr) {
		USkeletalMeshComponent* skeletalMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
		ensureMsgf(skeletalMesh != nullptr, TEXT("Skeletal Mesh can't be found!"));
		if (handIKType == EHandIKType::Trace) {
			FHitResult hitResult;
			FVector tracePos = skeletalMesh->GetSocketLocation(hand == EHandType::Left ? leftBoneName : rightBoneName);
			FVector traceEnd = tracePos + GetOwner()->GetActorForwardVector() * distance;
			ECollisionChannel channel = UEngineTypes::ConvertToCollisionChannel(interactChannel);

			if (GetWorld()->LineTraceSingleByChannel(hitResult, tracePos, traceEnd, channel))
			{
				//Position hand at impact point
				interactPoint = hitResult.ImpactPoint;
			}
			else {
				interactPoint = FVector();
			}
		}
		else {
			if (hand == EHandType::Left) {
				interactPoint = IIInteractable::Execute_GetLeftInteractPoint(currentInteractable);
				DrawDebugSphere(GetWorld(), interactPoint, 10.f, 12, FColor::Green, false, 5.0f);
				FMatrix localToWorldInverse = FMatrix(skeletalMesh->GetComponentTransform().ToMatrixWithScale().Inverse());
				interactPoint = localToWorldInverse.TransformPosition(interactPoint);
			}
			else {
				interactPoint = IIInteractable::Execute_GetRightInteractPoint(currentInteractable);
				DrawDebugSphere(GetWorld(), interactPoint, 10.f, 12, FColor::Cyan, false, 5.0f);
				FMatrix localToWorldInverse = FMatrix(skeletalMesh->GetComponentTransform().ToMatrixWithScale().Inverse());
				interactPoint = localToWorldInverse.TransformPosition(interactPoint);
			}
		}
	}
	return interactPoint;
}