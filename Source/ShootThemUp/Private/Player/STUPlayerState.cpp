// Shoot Them Up Game. All Rights Reserved.

#include "Player/STUPlayerState.h"

FLinearColor ASTUPlayerState::GetTeamColor() const {
	return TeamColor;
}

int32 ASTUPlayerState::GetTeamID() const {
	return TeamID;
}

void ASTUPlayerState::SetTeamColor(FLinearColor Color) {
	TeamColor = Color;
}

void ASTUPlayerState::SetTeamID(int32 Team) {
	TeamID = Team;
}
