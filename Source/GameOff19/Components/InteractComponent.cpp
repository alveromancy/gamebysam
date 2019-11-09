#include "InteractComponent.h"

UInteractComponent::UInteractComponent() {

}

bool UInteractComponent::Interact() {
	FHitResult hitResult;
	FVector tracePos = GetOwner()->GetActorLocation() + offset;
	FVector traceEnd = tracePos + GetOwner()->GetActorForwardVector() * distance;
	ECollisionChannel channel = UEngineTypes::ConvertToCollisionChannel(interactChannel);
	if (GetWorld()->LineTraceSingleByChannel(hitResult, tracePos, traceEnd, channel))
	{
		if (hitResult.Actor.Get()->GetClass()->ImplementsInterface(UIInteractable::StaticClass()))
		{
			IIInteractable::Execute_Interact(hitResult.Actor.Get(), interactType, handIKType);
			currentInteractable = hitResult.Actor.Get();
			hitResult.GetActor()->AttachToComponent(GetOwner()->FindComponentByClass<USkeletalMeshComponent>(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, interactSocketName);
			return true;
		}
	}

	return false;
}

FVector UInteractComponent::GetInteractPoint(const EHandType hand) {
	
	if (handIKType == EHandIKType::Trace) {
		FHitResult hitResult;
		FVector tracePos = GetOwner()->FindComponentByClass<USkeletalMeshComponent>()->GetSocketLocation(hand == EHandType::Left ? leftBoneName : rightBoneName);
		FVector traceEnd = tracePos + GetOwner()->GetActorForwardVector() * distance;
		ECollisionChannel channel = UEngineTypes::ConvertToCollisionChannel(interactChannel);

		if (GetWorld()->LineTraceSingleByChannel(hitResult, tracePos, traceEnd, channel))
		{
			//Position hand at impact point
			return hitResult.ImpactPoint;
		}
		else {
			return FVector();
		}
	}
	else {
		if (hand == EHandType::Left) {
			return IIInteractable::Execute_GetLeftInteractPoint(currentInteractable);
		}
		else {
			return IIInteractable::Execute_GetRightInteractPoint(currentInteractable);
		}
	}
}