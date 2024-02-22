// Shoot Them Up Game. All Rights Reserved.

#include "UI/STUPlayerHUDWidget.h"

#include "Components/ProgressBar.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "Player/STUPlayerController.h"
#include <Player/STUPlayerState.h>
#include "STUUtils.h"

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
		return HealthComponent->GetHealthPercent() / 100.f;
	}
	return 0.f;
}

int32 USTUPlayerHUDWidget::GetKills() const {
	const auto* PlayerState = GetOwningPlayerState<ASTUPlayerState>();
	if (!PlayerState) {
		return {};
	}
	return PlayerState->GetKills();
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

void USTUPlayerHUDWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();

	if (auto* Controller = GetOwningPlayer<ASTUPlayerController>()) {
		if (!Controller->OnPawnPossess.IsBoundToObject(this)) {
			Controller->OnPawnPossess.AddUObject(this, &USTUPlayerHUDWidget::OnNewPawn);
		}
	}
	OnNewPawn();
}

void USTUPlayerHUDWidget::InitializeDamageEvent() {
	if (auto* HealthComponent = STUUtils::GetComponentByClass<USTUHealthComponent>(GetOwningPlayerPawn())) {
		if (!HealthComponent->OnHealthChange.IsBoundToObject(this)) {
			HealthComponent->OnHealthChange.AddUObject(this, &USTUPlayerHUDWidget::OnHealthChanged);
		}
	}
}

void USTUPlayerHUDWidget::OnNewPawn() {
	InitializeDamageEvent();
	UpdateHealthBar();
}

void USTUPlayerHUDWidget::OnHealthChanged(float Delta) {
	if (Delta < 0.f) {
		OnTakeDamage();
	}
	UpdateHealthBar();
}

void USTUPlayerHUDWidget::UpdateHealthBar() const {
	if (!HealthProgressBar) {
		return;
	}
	const auto Percent = GetHealthPercent();
	HealthProgressBar->SetFillColorAndOpacity((Percent > PercentColorThreshold) ? DefaultColor : LowColor);
}
