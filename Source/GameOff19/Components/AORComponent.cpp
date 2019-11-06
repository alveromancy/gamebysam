#include "AORComponent.h"

UAORComponent::UAORComponent() {
	state = EAOR::Receiver;
}

void UAORComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
	
	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UAORComponent, state))
	{
		if (state == EAOR::Receiver) {
			receivers.Empty();
		}
	}
}

void UAORComponent::Send_Implementation() {
	
	UAORComponent* aor;
	for (auto const& receiver : receivers)
	{
		aor = Cast<UAORComponent>(receiver->FindComponentByClass(UAORComponent::StaticClass()));
		if(aor && aor->state == EAOR::Receiver && aor->OnReceive.IsBound())
			aor->OnReceive.Broadcast();
	}
}