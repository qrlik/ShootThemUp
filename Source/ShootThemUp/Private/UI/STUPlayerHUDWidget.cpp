// Shoot Them Up Game. All Rights Reserved.

#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"

FWeaponUIData USTUPlayerHUDWidget::GetWeaponUIData() const {
	if (const auto* Pawn = GetOwningPlayerPawn()) {
		if (const auto* WeaponComponent = Pawn->GetComponentByClass<USTUWeaponComponent>()) {
			return WeaponComponent->GetUIData();
		}
	}
	return {};
}

float USTUPlayerHUDWidget::GetHealthPercent() const {
	if (const auto* Pawn = GetOwningPlayerPawn()) {
		if (const auto* HealthComponent = Pawn->GetComponentByClass<USTUHealthComponent>()) {
			return HealthComponent->GetHealthPercent();
		}
	}
	return 0.f;
}
