// Shoot Them Up Game. All Rights Reserved.

#include "AI/Services/ChangeWeaponService.h"

#include "AIController.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

namespace {
	APawn* GetPawn(const AAIController* Controller) {
		if (Controller) {
			return Controller->GetPawn();
		}
		return nullptr;
	}
}

UChangeWeaponService::UChangeWeaponService() {
}

void UChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	TryToChangeWeapon(OwnerComp);
}

bool UChangeWeaponService::RollWeaponChange() const {
	const auto Roll = FMath::RandRange(0.f, 1.f);
	if (Roll < Probability || FMath::IsNearlyEqual(Roll, Probability)) {
		return true;
	}
	return false;
}

void UChangeWeaponService::TryToChangeWeapon(UBehaviorTreeComponent& OwnerComp) const {
	if (!RollWeaponChange()) {
		return;
	}

	if (auto* WeaponComponent = STUUtils::GetComponentByClass<USTUWeaponComponent>(GetPawn(OwnerComp.GetAIOwner()))) {
		if (WeaponComponent->IsNextWeaponCanFire()) {
			WeaponComponent->NextWeapon();
		}
	}
}
