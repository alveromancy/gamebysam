// Fill out your copyright notice in the Description page of Project Settings.


#include "Super_Platform.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"





// Sets default values
ASuper_Platform::ASuper_Platform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	S_Path = CreateDefaultSubobject<USplineComponent>("Path"); 
	RootComponent = S_Path;

	SM_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SM_Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	SM_Mesh->SetRelativeLocation(FVector());


	SC_Collider = CreateDefaultSubobject<USphereComponent>("Trigger"); 
	SC_Collider->AttachToComponent(SM_Mesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

	SC_Collider->OnComponentBeginOverlap.AddDynamic(this, &ASuper_Platform::PlayerDetected);
	SC_Collider->OnComponentEndOverlap.AddDynamic(this, &ASuper_Platform::PlayerDetectionLost);

	bWantsToDeactivate = false; 
}

// Called when the game starts or when spawned
void ASuper_Platform::BeginPlay()
{
	Super::BeginPlay();

	if (Activation == EPlatformActivation::AUTO)
		ActivatePlatform();
	else 
		DisablePlatform();
	
}

// Called every frame
void ASuper_Platform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentTime += (!bIsReverse - bIsReverse) * DeltaTime;
	if (CurrentTime > Time || CurrentTime < 0)
		EdgeReached();

	MovePlatform(); //Take care of frame loss (even we are on the edge this frames doesn't count)


	if (bShouldRotate)
	{
		RotatePlatform();
	}

}

void ASuper_Platform::MovePlatform()
{
	FVector Location = S_Path->GetLocationAtTime(CurrentTime, ESplineCoordinateSpace::Local);
	SM_Mesh->SetRelativeLocation(Location);
}


void ASuper_Platform::RotatePlatform()
{
	FRotator Rotation (S_Path->GetRotationAtTime(CurrentTime, ESplineCoordinateSpace::Local));
	SM_Mesh->SetRelativeRotation(Rotation); 	
}


void ASuper_Platform::EdgeReached()
{
	if (bWantsToDeactivate)
		DisablePlatform();
	else if (Movement == EPlatformMovement::ONE_WAY)
	{
		
		if (!bWantsToDeactivate && bShouldReset) //Okay we need to go back to original position
		{
			bWantsToDeactivate = true; //Platform is moving, but when arrives on the oposite edge, will stop
		}	
		else //We don't need to go back
			DisablePlatform(); //Deactivate
	}

	if (Movement == EPlatformMovement::LOOP)
	{
		CurrentTime = 0; 
	}
	else 
		bIsReverse = !bIsReverse; 
}

void ASuper_Platform::ActivatePlatform()
{
	if (!bWantsToDeactivate)
	{
		SetActorTickEnabled(true); 
		bIsActivated = true; 

		if (Deactivation == EPlatformDeactivation::TIMER)
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASuper_Platform::TimeOut, TimerToDeactivate, false, TimerToDeactivate);
		}
			
	}
}


void ASuper_Platform::DeactivatePlatform()
{
	if (bIsActivated)
	{

		if (bShouldReset)
		{
			bIsReverse = true;
			bWantsToDeactivate = true;
		}
		else
			DisablePlatform();
	}
	
}


void ASuper_Platform::DisablePlatform()
{
	SetActorTickEnabled(false);
	bIsActivated = false;
	bWantsToDeactivate = false; 
}

void ASuper_Platform::Reset()
{

}


void ASuper_Platform::TimeOut()
{
	bTimeGone = true; 
	DeactivatePlatform();
}



void ASuper_Platform::PlayerDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsActivated)
	{
		if (Activation == EPlatformActivation::PLAYER_STEP_UP)
		{
			ActivatePlatform();
		}
		OnPlayerDetected.Broadcast();
	}
	
}



void ASuper_Platform::PlayerDetectionLost(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (Deactivation == EPlatformDeactivation::PLAYER_STEP_DOWN)
	{
		DeactivatePlatform();
	}
	
	OnPlyaerUndetected.Broadcast();
}



#if WITH_EDITOR

void ASuper_Platform::PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;


	if (PropertyName == GET_MEMBER_NAME_CHECKED(ASuper_Platform, Time))
	{
		if (S_Path)
		{
			S_Path->Duration = Time; 
			CurrentTime = Time * StartingPoint;
		}
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(ASuper_Platform, StartingPoint))
	{
		if (SM_Mesh)
		{
			CurrentTime = Time * StartingPoint; 
			FVector Location = S_Path->GetLocationAtTime(CurrentTime, ESplineCoordinateSpace::Local); 
			SM_Mesh->SetRelativeLocation(Location); 
		}
			
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(ASuper_Platform, Activation))
	{
		if (Activation == EPlatformActivation::AUTO)
			bIsActivated = true; 

		if (Activation == EPlatformActivation::PLAYER_STEP_UP)
		{
			SC_Collider->SetCollisionProfileName("EventTrigger");
		}
		else
		{
			SC_Collider->SetCollisionProfileName("NoCollision"); 
		}
	}
}

#endif