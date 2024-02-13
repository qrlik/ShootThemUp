// Shoot Them Up Game. All Rights Reserved.

#include "UI/STUMatchInfoWidget.h"

#include "STUGameModeBase.h"
#include "Player/STUPlayerState.h"

ASTUGameModeBase* USTUMatchInfoWidget::GetGameMode() const {
	if (const auto* World = GetWorld()) {
		return World->GetAuthGameMode<ASTUGameModeBase>();
	}
	return nullptr;
}

float USTUMatchInfoWidget::GetRemainingTime() const {
	if (const auto* GameMode = GetGameMode()) {
		return GameMode->GetRoundRemainingTime();
	}
	return 0.f;
}

FIntPoint USTUMatchInfoWidget::GetRoundsInfo() const {
	const auto* GameMode = GetGameMode();
	if (!GameMode) {
		return {};
	}
	const auto CurrentRound = GameMode->GetCurrentRound();
	const auto RoundsAmount = GameMode->GetGameData().RoundsAmount;
	return { CurrentRound, RoundsAmount };
}

int32 USTUMatchInfoWidget::GetKills() const {
	const auto* PlayerState = GetOwningPlayerState<ASTUPlayerState>();
	if (!PlayerState) {
		return {};
	}
	return PlayerState->GetKills();
}
