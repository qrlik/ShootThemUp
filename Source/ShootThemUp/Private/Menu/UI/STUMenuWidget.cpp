// Shoot Them Up Game. All Rights Reserved.

#include "Menu/UI/STUMenuWidget.h"

#include "STUGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(STUMenuWidget, All, All)

void USTUMenuWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();

	InitStartGameButton();
}

void USTUMenuWidget::InitStartGameButton() {
	if (StartGameButton) {
		StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartGame);
	}
}

void USTUMenuWidget::OnStartGame() {
	const auto* World = GetWorld();
	if (!World) {
		return;
	}
	const auto* GameInstance = World->GetGameInstance<USTUGameInstance>();
	if (!GameInstance) {
		return;
	}

	const auto& StartupLevelName = GameInstance->GetStartupLevelName();
	if (StartupLevelName.IsNone()) {
		UE_LOG(STUMenuWidget, Error, TEXT("Startup level is None"));
		return;
	}
	UGameplayStatics::OpenLevel(this, StartupLevelName);
}
