// Shoot Them Up Game. All Rights Reserved.

#include "UI/STUMatchInfoWidget.h"

#include "Player/STUPlayerState.h"
#include "STUGameModeBase.h"
#include "STUUtils.h"

float USTUMatchInfoWidget::GetRemainingTime() const {
	if (const auto* GameMode = STUUtils::GetGameMode<ASTUGameModeBase>(GetWorld())) {
		return GameMode->GetRoundRemainingTime();
	}
	return 0.f;
}

FIntPoint USTUMatchInfoWidget::GetRoundsInfo() const {
	const auto* GameMode = STUUtils::GetGameMode<ASTUGameModeBase>(GetWorld());
	if (!GameMode) {
		return {};
	}
	const auto CurrentRound = GameMode->GetCurrentRound();
	const auto RoundsAmount = GameMode->GetGameData().RoundsAmount;
	return { CurrentRound, RoundsAmount };
}
