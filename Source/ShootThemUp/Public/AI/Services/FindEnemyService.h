// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FindEnemyService.generated.h"

UCLASS()
class SHOOTTHEMUP_API UFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
	UFindEnemyService();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

private:
	void UpdateEnemyActor(UBehaviorTreeComponent& OwnerComp) const;
};
