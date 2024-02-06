// Shoot Them Up Game. All Rights Reserved.

#include "AI/Services/FireService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

UFireService::UFireService() {
	NodeName = "Fire";
}

void UFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UpdateFire(OwnerComp);
}

void UFireService::UpdateFire(UBehaviorTreeComponent& OwnerComp) const {
	const auto* Blackboard = OwnerComp.GetBlackboardComponent();
	auto* WeaponComponent = STUUtils::GetComponentByClass<USTUWeaponComponent>(STUUtils::GetPawn(OwnerComp.GetAIOwner()));
	if (!WeaponComponent || !Blackboard) {
		return;
	}

	if (Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName)) {
		WeaponComponent->StartFire();
	}
	else {
		WeaponComponent->StopFire();
	}
}
