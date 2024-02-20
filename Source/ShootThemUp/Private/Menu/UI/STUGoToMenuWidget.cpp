// Shoot Them Up Game. All Rights Reserved.


#include "Menu/UI/STUGoToMenuWidget.h"

#include "Components/Button.h"
#include "STUGameInstance.h"
#include "STUUtils.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(STUGoToMenuWidget, All, All)

void USTUGoToMenuWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();

	InitGoToMenuButton();
}

void USTUGoToMenuWidget::InitGoToMenuButton() const {
	if (GoToMenuButton) {
		GoToMenuButton->OnClicked.AddDynamic(this, &USTUGoToMenuWidget::GoToMenu);
	}
}

void USTUGoToMenuWidget::GoToMenu() {
	const auto* GameInstance = STUUtils::GetGameInstance<USTUGameInstance>(GetWorld());
	if (!GameInstance) {
		return;
	}

	const auto& MenuLevelName = GameInstance->GetMenuLevelName();
	if (MenuLevelName.IsNone()) {
		UE_LOG(STUGoToMenuWidget, Error, TEXT("Menu level is None"));
		return;
	}
	UGameplayStatics::OpenLevel(this, MenuLevelName);
}
