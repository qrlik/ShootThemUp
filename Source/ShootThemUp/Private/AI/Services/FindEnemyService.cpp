// Shoot Them Up Game. All Rights Reserved.

#include "AI/Services/FindEnemyService.h"

#include "AI/STUAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UFindEnemyService::UFindEnemyService() {
	NodeName = "Find Enemy";
}

void UFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UpdateEnemyActor(OwnerComp);
}

void UFindEnemyService::UpdateEnemyActor(UBehaviorTreeComponent& OwnerComp) const {
	auto* Blackboard = OwnerComp.GetBlackboardComponent();
	const auto* Controller = Cast<ASTUAIController>(OwnerComp.GetAIOwner());
	if (!Blackboard || !Controller) {
		return;
	}
	Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, Controller->GetEnemyActor().Get());
}
