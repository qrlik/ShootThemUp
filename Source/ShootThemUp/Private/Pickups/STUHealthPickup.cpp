// Shoot Them Up Game. All Rights Reserved.

#include "Pickups/STUHealthPickup.h"

#include "Components/STUHealthComponent.h"
#include "Player/STUBaseCharacter.h"

bool ASTUHealthPickup::GiveToImpl(ASTUBaseCharacter* Character) const {
	if (!Character) {
		return false;
	}
	if (auto* HealthComponent = Character->GetHealthComponent()) {
		return HealthComponent->TryToAddHealth(RestoreHealth);
	}
	return false;
}
