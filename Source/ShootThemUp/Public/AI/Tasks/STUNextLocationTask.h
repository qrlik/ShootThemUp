// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "STUNextLocationTask.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUNextLocationTask : public UBTTaskNode {
	GENERATED_BODY()

public:
	USTUNextLocationTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector LocationKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	float Radius = 1000.f;
};
