// Shoot Them Up Game. All Rights Reserved.

#include "AI/Tasks/STUNextLocationTask.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

USTUNextLocationTask::USTUNextLocationTask() {
	NodeName = "Next Location";
}

EBTNodeResult::Type USTUNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	const auto* Controller = OwnerComp.GetAIOwner();
	const auto* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	auto* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !NavSys || !Blackboard) {
		return EBTNodeResult::Failed;
	}
	const auto* Pawn = Controller->GetPawn();
	if (!Pawn) {
		return EBTNodeResult::Failed;
	}

	FNavLocation NavLocation;
	if (!NavSys->GetRandomReachablePointInRadius(Pawn->GetActorLocation(), Radius, NavLocation)) {
		return EBTNodeResult::Failed;
	}
	Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);
	return EBTNodeResult::Succeeded;
}
