// Fill out your copyright notice in the Description page of Project Settings.


#include "SwitchButton.h"

// Sets default values
ASwitchButton::ASwitchButton() {

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	desiredState = false;
	isToggle = false;
	hasTimer = false;
	countdownTime = 0.0f;
	timeOutState = false;
}

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

void ASwitchButton::SwitchStateTo(bool desiredState) {
	state = desiredState;
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
void ASwitchButton::Interact_Implementation() {
	
	//State
	if (isToggle)
		ToggleState();
	else
		SwitchStateTo(desiredState);

	if (hasTimer)
		StartTimer();

	//Animation IK
}

FVector ASwitchButton::GetLeftInteractPoint_Implementation() const {
	FTransform socketTransform;
	if (leftHandSocket->GetSocketTransform(socketTransform, meshComponent))
		return socketTransform.GetLocation();
	else
		return GetActorLocation();
}

FVector ASwitchButton::GetRightInteractPoint_Implementation() const {
	FTransform socketTransform;
	if (leftHandSocket->GetSocketTransform(socketTransform, meshComponent))
		return socketTransform.GetLocation();
	else
		return GetActorLocation();
}