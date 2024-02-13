// Shoot Them Up Game. All Rights Reserved.

#include "Components/STURespawnComponent.h"

#include "STUGameModeBase.h"

void USTURespawnComponent::StartRespawn(float Respawn) {
	const auto* World = GetWorld();
	if (RespawnTimer.IsValid() || !World) {
		return;
	}
	World->GetTimerManager().SetTimer(RespawnTimer, this, &USTURespawnComponent::Respawn, Respawn);
}

void USTURespawnComponent::Reset() {
	const auto* World = GetWorld();
	if (!World) {
		RespawnTimer.Invalidate();
		return;
	}
	World->GetTimerManager().ClearTimer(RespawnTimer);
}

void USTURespawnComponent::Respawn() {
	Reset();

	if (const auto* World = GetWorld()) {
		if (auto* GameMode = World->GetAuthGameMode<ASTUGameModeBase>()) {
			GameMode->OnRespawn(Cast<AController>(GetOwner()));
		}
	}
}
