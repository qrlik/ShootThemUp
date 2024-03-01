// Shoot Them Up Game. All Rights Reserved.

#include "STUUtils.h"

#include "Player/STUPlayerState.h"

APawn* STUUtils::GetPawn(const AController* Controller) {
	if (Controller) {
		return Controller->GetPawn();
	}
	return nullptr;
}

bool STUUtils::AreEnemies(const AController* Lhs, const AController* Rhs) {
	if (!Lhs || !Rhs || Lhs == Rhs) {
		return false;
	}
	const auto* LhsState = Lhs->GetPlayerState<ASTUPlayerState>();
	const auto* RhsState = Rhs->GetPlayerState<ASTUPlayerState>();
	if (LhsState && RhsState) {
		return LhsState->GetTeamID() != RhsState->GetTeamID();
	}
	return false;
}
