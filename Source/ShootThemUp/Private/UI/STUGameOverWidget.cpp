// Shoot Them Up Game. All Rights Reserved.

#include "UI/STUGameOverWidget.h"

#include "STUGameModeBase.h"
#include "STUUtils.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Player/STUPlayerState.h"
#include "UI/STUPlayerStatRowWidget.h"

void USTUGameOverWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();

	InitMatchStateDelegate();
	InitResetLevelButton();
}

void USTUGameOverWidget::InitMatchStateDelegate() {
	if (auto* GameMode = STUUtils::GetGameMode<ASTUGameModeBase>(GetWorld())) {
		check(!GameMode->OnMatchStateChange.IsBoundToObject(this));
		GameMode->OnMatchStateChange.AddUObject(this, &USTUGameOverWidget::OnMatchStateChanged);
	}
}

void USTUGameOverWidget::InitResetLevelButton() {
	if (ResetLevelButton) {
		ResetLevelButton->OnClicked.AddDynamic(this, &USTUGameOverWidget::OnResetLevel);
	}
}

void USTUGameOverWidget::OnMatchStateChanged(EMatchState State) {
	if (State == EMatchState::GameOver) {
		UpdatePlayersStat();
	}
}

void USTUGameOverWidget::OnResetLevel() {
	const auto CurrentLevelName = FName{ UGameplayStatics::GetCurrentLevelName(this) };
	UGameplayStatics::OpenLevel(this, CurrentLevelName);
}

void USTUGameOverWidget::UpdatePlayersStat() {
	const auto* World = GetWorld();
	if (!World || !PlayersStatBox) {
		return;
	}
	PlayersStatBox->ClearChildren();

	for (auto It = World->GetControllerIterator(); It; ++It) {
		const auto* Controller = It->Get();
		const auto* PlayerState = STUUtils::GetPlayerState<ASTUPlayerState>(Controller);
		if (!PlayerState) {
			continue;
		}

		const auto PlayerStateWidget = CreateWidget<USTUPlayerStatRowWidget>(this, PlayerStatRowClass);
		if (!PlayerStateWidget) {
			continue;
		}

		PlayersStatBox->AddChild(PlayerStateWidget);
		PlayerStateWidget->SetPlayerIndicator(Controller->IsPlayerController());
		PlayerStateWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
		PlayerStateWidget->SetKills(FText::FromString(FString::FromInt(PlayerState->GetKills())));
		PlayerStateWidget->SetDeaths(FText::FromString(FString::FromInt(PlayerState->GetDeaths())));
		PlayerStateWidget->SetTeam(FText::FromString(FString::FromInt(PlayerState->GetTeamID())));
		PlayerStateWidget->SetTeamColor(PlayerState->GetTeamColor());
	}
}
