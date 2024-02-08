// Shoot Them Up Game. All Rights Reserved.

#include "AI/Decorators/BTDecorator_NeedAmmo.h"

#include "AIController.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

UBTDecorator_NeedAmmo::UBTDecorator_NeedAmmo() {
	NodeName = "Need Ammo";
}

bool UBTDecorator_NeedAmmo::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
	if (!WeaponType) {
		UE_LOG(LogInit, Error, TEXT("UBTDecorator_NeedAmmo don't have WeaponType"));
		return false;
	}
	const auto* Pawn = STUUtils::GetPawn(OwnerComp.GetAIOwner());
	const auto* WeaponComponent = STUUtils::GetComponentByClass<USTUWeaponComponent>(Pawn);
	if (!WeaponComponent) {
		return false;
	}
	if (const auto* Weapon = WeaponComponent->GetWeapon(WeaponType)) {
		return !Weapon->IsAmmoFull();
	}
	return false;
}
