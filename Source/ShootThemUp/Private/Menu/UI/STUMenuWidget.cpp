// Shoot Them Up Game. All Rights Reserved.

#include "Menu/UI/STUMenuWidget.h"

#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Menu/UI/STULevelItemWidget.h"
#include "STUCoreTypes.h"
#include "STUGameInstance.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(STUMenuWidget, All, All)

void USTUMenuWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();

	InitStartGameButton();
	InitQuitGameButton();
	InitLevelItemsBox();
}

void USTUMenuWidget::InitStartGameButton() {
	if (StartGameButton) {
		StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartGame);
	}
}

void USTUMenuWidget::InitQuitGameButton() {
	if (QuitGameButton) {
		QuitGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnQuitGame);
	}
}

void USTUMenuWidget::InitLevelItemsBox() {
	const auto* GameInstance = STUUtils::GetGameInstance<USTUGameInstance>(GetWorld());
	if (!GameInstance || !LevelItemsBox) {
		return;
	}
	LevelItemsBox->ClearChildren();
	const auto& Levels = GameInstance->GetLevelsData();
	checkf(Levels.Num() > 0, TEXT("Empty levels data"));
	const auto& LastPlayedLevel = GameInstance->GetLastLevelName();

	for (const auto& LevelData : Levels) {
		auto* LevelItemWidget = CreateWidget<USTULevelItemWidget>(this, LevelItemWidgetClass);
		if (!LevelItemWidget) {
			continue;
		}
		LevelItemsBox->AddChild(LevelItemWidget);
		LevelItemWidgets.Add(LevelItemWidget);

		LevelItemWidget->SetLevelData(LevelData);
		check(!LevelItemWidget->OnLevelSelected.IsBoundToObject(this));
		LevelItemWidget->OnLevelSelected.BindUObject(this, &USTUMenuWidget::OnLevelSelected);

		if (LastPlayedLevel == LevelData.LevelName) {
			SelectLevel(LevelItemWidget);
		}
	}

	if (!SelectedLevelItemWidget) {
		SelectLevel(Cast<USTULevelItemWidget>(LevelItemsBox->GetChildAt(0)));
	}
}

void USTUMenuWidget::OnStartGame() {
	auto* GameInstance = STUUtils::GetGameInstance<USTUGameInstance>(GetWorld());
	if (!GameInstance) {
		return;
	}
	if (!SelectedLevelItemWidget) {
		UE_LOG(STUMenuWidget, Error, TEXT("Level not selected"));
		return;
	}
	GameInstance->LoadLevel(SelectedLevelItemWidget->GetLevelData().LevelName);
}

void USTUMenuWidget::OnQuitGame() {
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USTUMenuWidget::OnLevelSelected(const FName& LevelName) {
	for (const auto& LevelWidget : LevelItemWidgets) {
		if (LevelWidget->GetLevelData().LevelName == LevelName) {
			SelectLevel(LevelWidget);
		}
	}
}

void USTUMenuWidget::SelectLevel(TObjectPtr<USTULevelItemWidget> LevelWidget) {
	if (!LevelWidget) {
		return;
	}
	if (SelectedLevelItemWidget) {
		SelectedLevelItemWidget->SetSelected(false);
	}
	LevelWidget->SetSelected(true);
	SelectedLevelItemWidget = LevelWidget;
}
