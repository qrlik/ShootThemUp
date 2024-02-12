// Shoot Them Up Game. All Rights Reserved.

#include "STUGameModeBase.h"

#include "AIController.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "UI/STUGameHUD.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameStateBase, All, All)

ASTUGameModeBase::ASTUGameModeBase() {
	DefaultPawnClass = ASTUBaseCharacter::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();
	HUDClass = ASTUGameHUD::StaticClass();
}

void ASTUGameModeBase::StartPlay() {
	SpawnBots();
	StartRound();

	Super::StartPlay();
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
		GetWorldTimerManager().SetTimer(RoundTimer, this, &ASTUGameModeBase::EndRound, Data.RoundTime);

		UE_LOG(LogGameStateBase, Display, TEXT("NEW ROUND - %i"), CurrentRound);
	}
}

void ASTUGameModeBase::EndRound() {
	GetWorldTimerManager().ClearTimer(RoundTimer);

	if (CurrentRound >= Data.RoundsAmount) {
		UE_LOG(LogGameStateBase, Display, TEXT("=========== GAME OVER ==========="));
	}
	else {
		StartRound();
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
