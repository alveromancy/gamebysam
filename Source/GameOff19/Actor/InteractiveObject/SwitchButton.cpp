// Fill out your copyright notice in the Description page of Project Settings.


#include "SwitchButton.h"
#include "Engine/StaticMeshSocket.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/AORComponent.h"

// Sets default values
ASwitchButton::ASwitchButton() {

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	isLocked = false;
	initialState = false;
	resultState = false;
	isToggle = false;
	isTimed = false;
	countdownTime = 0.f;
	state = false;

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	ensureMsgf(SetRootComponent(mesh), TEXT("Can't set mesh to root component!"));
	AORComponent = CreateDefaultSubobject<UAORComponent>(TEXT("ActivateReceiverComponent"));
}

#if WITH_EDITOR
void ASwitchButton::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ASwitchButton, isToggle))
	{
		if (isToggle)
			resultState = false;
	}
	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ASwitchButton, isTimed))
	{
		if (!isTimed) {
			countdownTime = 0.f;
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

void ASwitchButton::ChangeLockState(bool State) {
	
	isLocked = State;
	if (isLocked)
	{
		OnLocked.Broadcast();
	}
	else {
		OnUnlocked.Broadcast();
	}
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
	SwitchStateTo(resultState);
	if (OnTimerFinished.IsBound())
		OnTimerFinished.Broadcast();
}

//Interaction
void ASwitchButton::Interact_Implementation(EInteractType& interactType) {

	if (isLocked)
		return;

	//State
	if (isToggle)
		ToggleState();
	else
		SwitchStateTo(resultState);

	if (isTimed)
		StartTimer();

	interactType = EInteractType::Interact;
}