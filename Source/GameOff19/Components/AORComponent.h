#pragma once

#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "AORComponent.generated.h"

UENUM()
enum class EAOR : uint8 {
	Activator,
	Receiver
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReceiveSignature);

UCLASS(BlueprintType, meta=(BlueprintSpawnableComponent, DisplayName = ActivatorOrReceiverComponent))
class GAMEOFF19_API UAORComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UAORComponent();
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
public:
	/*Call to activate receivers.*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = AOR)
	void Send();
	virtual void Send_Implementation();
	/*Activate receiver.*/
	UPROPERTY(BlueprintAssignable, Category=AOR)
	FReceiveSignature OnReceive;

public:
	UPROPERTY(EditAnywhere, Category = AOR)
	EAOR state;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (EditCondition = "state == EAOR::Activator"), Category = AOR)
	TArray<AActor*> receivers;
};