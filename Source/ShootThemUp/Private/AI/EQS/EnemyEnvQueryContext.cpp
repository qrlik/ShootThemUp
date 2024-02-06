// Shoot Them Up Game. All Rights Reserved.

#include "AI/EQS/EnemyEnvQueryContext.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const {
	auto* QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
	const auto* Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
	if (!Blackboard) {
		return;
	}
	const auto* EnemyActor = Cast<AActor>(Blackboard->GetValueAsObject(EnemyActorKey));
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, EnemyActor);
}
