// Shoot Them Up Game. All Rights Reserved.

#include "STUGameModeBase.h"

#include "AIController.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "Player/STUPlayerState.h"
#include "UI/STUGameHUD.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameStateBase, All, All)

ASTUGameModeBase::ASTUGameModeBase() {
	DefaultPawnClass = ASTUBaseCharacter::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();
	PlayerStateClass = ASTUPlayerState::StaticClass();
	HUDClass = ASTUGameHUD::StaticClass();
}

void ASTUGameModeBase::StartPlay() {
	SpawnBots();
	CreateTeamsInfo();

	StartRound();

	Super::StartPlay();
}

void ASTUGameModeBase::Killed(const AController* KillerController, const AController* VictimController) const {
	if (!KillerController || !VictimController) {
		return;
	}
	if (auto* KillerState = KillerController->GetPlayerState<ASTUPlayerState>()) {
		KillerState->OnKill();
	}
	if (auto* VictimState = VictimController->GetPlayerState<ASTUPlayerState>()) {
		VictimState->OnDeath();
	}
}

const FGameData& ASTUGameModeBase::GetGameData() const {
	return Data;
}

float ASTUGameModeBase::GetRoundRemainingTime() const {
	if (RoundTimer.IsValid()) {
		return GetWorldTimerManager().GetTimerRemaining(RoundTimer);
	}
	return 0.f;
}

int32 ASTUGameModeBase::GetCurrentRound() const {
	return CurrentRound;
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController) {
	if (InController && InController->IsPlayerController()) {
		return Super::GetDefaultPawnClassForController_Implementation(InController);
	}
	return AIPawnClass;
}

void ASTUGameModeBase::StartRound() {
	if (!RoundTimer.IsValid()) {
		CurrentRound += 1;
		ResetPlayers();

		GetWorldTimerManager().SetTimer(RoundTimer, this, &ASTUGameModeBase::EndRound, Data.RoundTime);

		UE_LOG(LogGameStateBase, Display, TEXT("NEW ROUND - %i"), CurrentRound);
	}
}

void ASTUGameModeBase::EndRound() {
	GetWorldTimerManager().ClearTimer(RoundTimer);

	if (CurrentRound >= Data.RoundsAmount) {
		UE_LOG(LogGameStateBase, Display, TEXT("=========== GAME OVER ==========="));
		LogPlayerInfo();
	}
	else {
		StartRound();
	}
}

void ASTUGameModeBase::SetPlayerColor(const AController* Controller) const {
	if (!Controller) {
		return;
	}
	const auto* PlayerState = Controller->GetPlayerState<ASTUPlayerState>();
	const auto* Character = Controller->GetPawn<ASTUBaseCharacter>();
	if (!PlayerState || !Character) {
		return;
	}
	Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void ASTUGameModeBase::ResetPlayer(AController* Controller) {
	if (Controller && Controller->GetPawn()) {
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void ASTUGameModeBase::ResetPlayers() {
	const auto* World = GetWorld();
	if (!World) {
		return;
	}
	for (auto It = World->GetControllerIterator(); It; ++It) {
		ResetPlayer(It->Get());
	}
}

void ASTUGameModeBase::LogPlayerInfo() const {
	const auto* World = GetWorld();
	if (!World) {
		return;
	}
	for (auto It = World->GetControllerIterator(); It; ++It) {
		const auto* Controller = It->Get();
		if (!Controller) {
			continue;
		}
		if (const auto* PlayerState = Controller->GetPlayerState<ASTUPlayerState>()) {
			PlayerState->Log();
		}
	}
}

FLinearColor ASTUGameModeBase::GetTeamColor(int32 TeamID) const {
	if (TeamID >= Data.TeamColors.Num() || TeamID < 0) {
		UE_LOG(LogGameStateBase, Warning, TEXT("GetTeamColor invalid Team ID"));
		return FLinearColor::White;
	}
	return Data.TeamColors[TeamID];
}

void ASTUGameModeBase::CreateTeamsInfo() const {
	const auto* World = GetWorld();
	if (!World) {
		return;
	}

	int32 TeamID = 0;
	const int32 TeamsAmount = Data.TeamColors.Num();
	for (auto It = World->GetControllerIterator(); It; ++It) {
		const auto* Controller = It->Get();
		if (!Controller) {
			continue;
		}
		auto* PlayerState = Controller->GetPlayerState<ASTUPlayerState>();
		if (!PlayerState) {
			continue;
		}

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(GetTeamColor(TeamID));
		SetPlayerColor(Controller);

		if (TeamsAmount > 0) {
			TeamID = (TeamID + 1) % TeamsAmount;
		}
	}
}

void ASTUGameModeBase::SpawnBots() {
	auto* World = GetWorld();
	if (!World) {
		return;
	}

	for (auto i = 0; i + 1 < Data.PlayersAmount; ++i) {
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		auto* Controller = World->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(Controller);
	}
}
