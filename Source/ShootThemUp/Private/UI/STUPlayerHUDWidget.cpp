﻿// Shoot Them Up Game. All Rights Reserved.

#include "UI/STUPlayerHUDWidget.h"

#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

namespace {
}

bool USTUPlayerHUDWidget::Initialize() {
	InitializeDamageEvent();
	return Super::Initialize();
}

FWeaponUIData USTUPlayerHUDWidget::GetCurrentWeaponUIData() const {
	if (const auto* WeaponComponent = STUUtils::GetComponentByClass<USTUWeaponComponent>(GetOwningPlayerPawn())) {
		return WeaponComponent->GetUIData();
	}
	return {};
}

FAmmoData USTUPlayerHUDWidget::GetCurrentWeaponAmmo() const {
	if (const auto* WeaponComponent = STUUtils::GetComponentByClass<USTUWeaponComponent>(GetOwningPlayerPawn())) {
		return WeaponComponent->GetAmmoData();
	}
	return {};
}

float USTUPlayerHUDWidget::GetHealthPercent() const {
	if (const auto* HealthComponent = STUUtils::GetComponentByClass<USTUHealthComponent>(GetOwningPlayerPawn())) {
		return HealthComponent->GetHealthPercent();
	}
	return 0.f;
}

bool USTUPlayerHUDWidget::IsPlayerAlive() const {
	if (const auto* HealthComponent = STUUtils::GetComponentByClass<USTUHealthComponent>(GetOwningPlayerPawn())) {
		return !HealthComponent->IsDead();
	}
	return false;
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const {
	if (const auto* Controller = GetOwningPlayer()) {
		return Controller->GetStateName() == NAME_Spectating;
	}
	return false;
}

void USTUPlayerHUDWidget::InitializeDamageEvent() {
	if (auto* HealthComponent = STUUtils::GetComponentByClass<USTUHealthComponent>(GetOwningPlayerPawn())) {
		HealthComponent->OnHealthChange.AddUObject(this, &USTUPlayerHUDWidget::OnHealthChanged);
	}
}

void USTUPlayerHUDWidget::OnHealthChanged(float Delta) {
	if (Delta < 0.f) {
		OnTakeDamage();
	}
}
