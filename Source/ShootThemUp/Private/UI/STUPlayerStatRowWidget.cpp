// Shoot Them Up Game. All Rights Reserved.

#include "UI/STUPlayerStatRowWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void USTUPlayerStatRowWidget::SetPlayerIndicator(bool State) const {
	if (PlayerIndicatorImage) {
		PlayerIndicatorImage->SetVisibility((State) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

void USTUPlayerStatRowWidget::SetPlayerName(const FText& Name) const {
	if (PlayerNameText) {
		PlayerNameText->SetText(Name);
	}
}

void USTUPlayerStatRowWidget::SetKills(const FText& Kills) const {
	if (KillsText) {
		KillsText->SetText(Kills);
	}
}

void USTUPlayerStatRowWidget::SetDeaths(const FText& Deaths) const {
	if (DeathsText) {
		DeathsText->SetText(Deaths);
	}
}

void USTUPlayerStatRowWidget::SetTeam(const FText& Team) const {
	if (TeamText) {
		TeamText->SetText(Team);
	}
}

void USTUPlayerStatRowWidget::SetTeamColor(FLinearColor Color) const {
	if (TeamImage) {
		TeamImage->SetColorAndOpacity(Color);
	}
}
