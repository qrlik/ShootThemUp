// Shoot Them Up Game. All Rights Reserved.

#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"

float USTUPlayerHUDWidget::GetHealthPercent() const {
	if (const auto* Pawn = GetOwningPlayerPawn()) {
		if (const auto* HealthComponent = Pawn->GetComponentByClass<USTUHealthComponent>()) {
			return HealthComponent->GetHealthPercent();
		}
	}
	return 0.f;
}
