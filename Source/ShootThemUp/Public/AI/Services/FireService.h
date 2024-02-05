// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FireService.generated.h"

UCLASS()
class SHOOTTHEMUP_API UFireService : public UBTService {
	GENERATED_BODY()

public:
	UFireService();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

private:
	void UpdateFire(UBehaviorTreeComponent& OwnerComp) const;
};
