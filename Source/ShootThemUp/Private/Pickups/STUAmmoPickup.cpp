// Shoot Them Up Game. All Rights Reserved.

#include "Pickups/STUAmmoPickup.h"
#include "Components/STUWeaponComponent.h"
#include "Player/STUBaseCharacter.h"

bool ASTUAmmoPickup::GiveToImpl(ASTUBaseCharacter* Character) const {
	if (!Character) {
		return false;
	}
	if (const auto* WeaponComponent = Character->GetWeaponComponent()) {
		return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
	}
	return false;
}
