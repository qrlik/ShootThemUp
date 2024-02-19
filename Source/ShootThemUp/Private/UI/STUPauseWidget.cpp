// Shoot Them Up Game. All Rights Reserved.

#include "UI/STUPauseWidget.h"

#include "Components/Button.h"
#include "STUGameModeBase.h"
#include "STUUtils.h"

void USTUPauseWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();

	InitClearPauseButton();
}

void USTUPauseWidget::InitClearPauseButton() {
	if (ClearPauseButton) {
		ClearPauseButton->OnClicked.AddDynamic(this, &USTUPauseWidget::OnClearPause);
	}
}

void USTUPauseWidget::OnClearPause() {
	if (auto* GameMode = STUUtils::GetGameMode<ASTUGameModeBase>(GetWorld())) {
		GameMode->ClearPause();
	}
}
