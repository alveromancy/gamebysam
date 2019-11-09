// Fill out your copyright notice in the Description page of Project Settings.


#include "SwitchButton.h"
#include "Engine/StaticMeshSocket.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASwitchButton::ASwitchButton() {

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	desiredState = false;
	isToggle = false;
	hasTimer = false;
	countdownTime = 0.f;
	timeOutState = false;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

#if WITH_EDITOR
void ASwitchButton::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {

	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ASwitchButton, isToggle))
	{
		if (!isToggle)
			desiredState = false;
	}
	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ASwitchButton, hasTimer))
	{
		if (!hasTimer) {
			countdownTime = 0.f;
			timeOutState = false;
		}
	}
}
#endif

// Called when the game starts or when spawned
void ASwitchButton::BeginPlay() {
	Super::BeginPlay();

}

// Called every frame
void ASwitchButton::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ASwitchButton::ToggleState() {
	state = !state;
	if (OnToggle.IsBound())
		OnToggle.Broadcast();
}

void ASwitchButton::SwitchStateTo(bool DesiredState) {
	state = DesiredState;
	if (OnStateChange.IsBound())
		OnStateChange.Broadcast();
}

void ASwitchButton::StartTimer() {
	GetWorldTimerManager().SetTimer(timerHandler, this, &ASwitchButton::TimerFinished, countdownTime, false);
	if (OnTimerStart.IsBound())
		OnTimerStart.Broadcast();
}

void ASwitchButton::TimerFinished() {
	GetWorldTimerManager().ClearTimer(timerHandler);
	SwitchStateTo(timeOutState);
	if (OnTimerFinished.IsBound())
		OnTimerFinished.Broadcast();
}

//Interaction
void ASwitchButton::Interact_Implementation(EInteractType& interactType, EHandIKType& handIKType) {

	//State
	if (isToggle)
		ToggleState();
	else
		SwitchStateTo(desiredState);

	if (hasTimer)
		StartTimer();

	interactType = EInteractType::Interact;
	handIKType = EHandIKType::Socket;
}

FVector ASwitchButton::GetLeftInteractPoint_Implementation() const {
	
	FVector interactPoint;
	if (mesh)
		interactPoint = mesh->GetSocketLocation(leftHandSocket);
	else
		interactPoint = GetActorLocation();

	return interactPoint;
}

FVector ASwitchButton::GetRightInteractPoint_Implementation() const {
	
	FVector interactPoint;
	if (mesh)
	{
		interactPoint = mesh->GetSocketLocation(rightHandSocket);
	}
	else
		interactPoint = GetActorLocation();

	return interactPoint;
}