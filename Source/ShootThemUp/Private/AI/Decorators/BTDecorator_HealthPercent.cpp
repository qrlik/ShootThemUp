// Shoot Them Up Game. All Rights Reserved.

#include "AI/Decorators/BTDecorator_HealthPercent.h"

#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUHealthComponent.h"

UBTDecorator_HealthPercent::UBTDecorator_HealthPercent() {
	NodeName = "Health Percent";
}

bool UBTDecorator_HealthPercent::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
	const auto* Pawn = STUUtils::GetPawn(OwnerComp.GetAIOwner());
	const auto* HealthComponent = STUUtils::GetComponentByClass<USTUHealthComponent>(Pawn);
	if (HealthComponent && !HealthComponent->IsDead()) {
		return HealthComponent->GetHealthPercent() < HealthPercent;
	}
	return false;
}
