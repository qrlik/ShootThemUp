// Shoot Them Up Game. All Rights Reserved.

#include "Menu/UI/STULevelItemWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


const FLevelData& USTULevelItemWidget::GetLevelData() const {
	return LevelData;
}

void USTULevelItemWidget::SetLevelData(const FLevelData& Data) {
	LevelData = Data;

	UpdateLevelName();
	UpdateLevelIcon();
}

void USTULevelItemWidget::SetSelected(bool State) const {
	if (LevelFrameImage) {
		LevelFrameImage->SetVisibility((State) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

void USTULevelItemWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();

	InitLevelSelectButton();
	InitLevelFrame();
}

void USTULevelItemWidget::InitLevelSelectButton() {
	if (LevelSelectButton) {
		check(!LevelSelectButton->OnClicked.IsBound());
		LevelSelectButton->OnClicked.AddDynamic(this, &USTULevelItemWidget::OnLevelIconClicked);
	}
}

void USTULevelItemWidget::UpdateLevelName() const {
	if (LevelNameText) {
		LevelNameText->SetText(FText::FromName(LevelData.LevelDisplayName));
	}
}

void USTULevelItemWidget::UpdateLevelIcon() const {
	if (LevelIconImage) {
		LevelIconImage->SetBrushFromTexture(LevelData.LevelIcon);
	}
}

void USTULevelItemWidget::InitLevelFrame() const {
	SetSelected(false);
}

void USTULevelItemWidget::OnLevelIconClicked() {
	verify(OnLevelSelected.ExecuteIfBound(LevelData.LevelName));
}
