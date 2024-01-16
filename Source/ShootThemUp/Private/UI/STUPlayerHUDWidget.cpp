// Shoot Them Up Game. All Rights Reserved.

#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"

namespace {
	template <typename T>
	T* GetComponentByClass(APawn* Pawn) {
		if (Pawn) {
			if (auto* Component = Pawn->GetComponentByClass<T>()) {
				return Component;
			}
		}
		return nullptr;
	}
}

FWeaponUIData USTUPlayerHUDWidget::GetCurrentWeaponUIData() const {
	if (const auto* WeaponComponent = GetComponentByClass<USTUWeaponComponent>(GetOwningPlayerPawn())) {
		return WeaponComponent->GetUIData();
	}
	return {};
}

FAmmoData USTUPlayerHUDWidget::GetCurrentWeaponAmmo() const {
	if (const auto* WeaponComponent = GetComponentByClass<USTUWeaponComponent>(GetOwningPlayerPawn())) {
		return WeaponComponent->GetAmmoData();
	}
	return {};
}

float USTUPlayerHUDWidget::GetHealthPercent() const {
	if (const auto* HealthComponent = GetComponentByClass<USTUHealthComponent>(GetOwningPlayerPawn())) {
		return HealthComponent->GetHealthPercent();
	}
	return 0.f;
}
