// Shoot Them Up Game. All Rights Reserved.

#include "Player/STUPlayerController.h"

#include "Components/STURespawnComponent.h"
#include "GameFramework/GameModeBase.h"
#include "STUGameModeBase.h"
#include "STUUtils.h"

ASTUPlayerController::ASTUPlayerController() {
	Respawn = CreateDefaultSubobject<USTURespawnComponent>("RespawnComponent");
}

void ASTUPlayerController::BeginPlay() {
	Super::BeginPlay();

	InitMatchStateDelegate();
}

void ASTUPlayerController::OnPossess(APawn* aPawn) {
	Super::OnPossess(aPawn);

	OnPawnPossess.Broadcast();
}

void ASTUPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	if (InputComponent) {
		InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASTUPlayerController::OnPauseGame);
	}
}

void ASTUPlayerController::InitMatchStateDelegate() {
	if (auto* GameMode = STUUtils::GetGameMode<ASTUGameModeBase>(GetWorld())) {
		check(!GameMode->OnMatchStateChange.IsBoundToObject(this));
		GameMode->OnMatchStateChange.AddUObject(this, &ASTUPlayerController::OnMatchStateChanged);
	}
}

void ASTUPlayerController::OnMatchStateChanged(EMatchState State) {
	if (State == EMatchState::InProgress) {
		SetInputMode(FInputModeGameOnly{});
		bShowMouseCursor = false;
	}
	else {
		SetInputMode(FInputModeUIOnly{});
		bShowMouseCursor = true;
	}
}

void ASTUPlayerController::OnPauseGame() {
	if (auto* GameMode = STUUtils::GetGameMode(GetWorld())) {
		GameMode->SetPause(this);
	}
}
