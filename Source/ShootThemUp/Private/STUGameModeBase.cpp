// Shoot Them Up Game. All Rights Reserved.

#include "STUGameModeBase.h"

#include "AIController.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "UI/STUGameHUD.h"

ASTUGameModeBase::ASTUGameModeBase() {
	DefaultPawnClass = ASTUBaseCharacter::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();
	HUDClass = ASTUGameHUD::StaticClass();
}

void ASTUGameModeBase::StartPlay() {
	SpawnBots();

	Super::StartPlay();
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController) {
	if (InController && InController->IsPlayerController()) {
		return Super::GetDefaultPawnClassForController_Implementation(InController);
	}
	return AIPawnClass;
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
