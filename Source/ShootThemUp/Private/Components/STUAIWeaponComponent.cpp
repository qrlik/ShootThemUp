// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUAIWeaponComponent.h"

void USTUAIWeaponComponent::OnEmptyClipImpl() {
	const auto* Current = GetCurrentWeapon();
	const auto* Next = GetNextWeapon();
	if (Current == Next || !Current || !Next) {
		return;
	}
	if (!Next->IsAmmoEmpty()) {
		if (Current->IsAmmoEmpty()) {
			NextWeapon();
		}
		else if (Current->GetAmmoData().Infinite) {
			bChangeWeaponAfterReload = true;
		}
	}
}

void USTUAIWeaponComponent::OnReloadFinishedImpl() {
	if (bChangeWeaponAfterReload) {
		bChangeWeaponAfterReload = false;
		NextWeapon();
	}
}
