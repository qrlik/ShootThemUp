// Shoot Them Up Game. All Rights Reserved.

#include "Player/STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerState, All, All)

FLinearColor ASTUPlayerState::GetTeamColor() const {
	return TeamColor;
}

int32 ASTUPlayerState::GetTeamID() const {
	return TeamID;
}

int32 ASTUPlayerState::GetKills() const {
	return KillsAmount;
}

int32 ASTUPlayerState::GetDeaths() const {
	return DeathAmount;
}

void ASTUPlayerState::OnKill() {
	++KillsAmount;
}

void ASTUPlayerState::OnDeath() {
	++DeathAmount;
}

void ASTUPlayerState::SetTeamColor(FLinearColor Color) {
	TeamColor = Color;
}

void ASTUPlayerState::SetTeamID(int32 Team) {
	TeamID = Team;
}

void ASTUPlayerState::Log() const {
	UE_LOG(LogPlayerState, Display, TEXT("TeamID: %i, Kills: %i, Deaths: %i"), TeamID, KillsAmount, DeathAmount);
}
