// Shoot Them Up Game. All Rights Reserved.

#include "UI/STUHealthBarWidget.h"

#include "Components/ProgressBar.h"

void USTUHealthBarWidget::SetHealthPercent(float Percent) const {
	if (!HealthProgressBar) {
		return;
	}
	if (Percent > PercentVisibilityThreshold || FMath::IsNearlyZero(Percent)) {
		HealthProgressBar->SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		HealthProgressBar->SetVisibility(ESlateVisibility::Visible);
		HealthProgressBar->SetFillColorAndOpacity((Percent > PercentColorThreshold) ? DefaultColor : LowColor);
		HealthProgressBar->SetPercent(Percent);
	}
}
