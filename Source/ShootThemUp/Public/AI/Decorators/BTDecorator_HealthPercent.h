// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_HealthPercent.generated.h"

UCLASS()
class SHOOTTHEMUP_API UBTDecorator_HealthPercent : public UBTDecorator {
	GENERATED_BODY()

public:
	UBTDecorator_HealthPercent();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, Category = "AI")
	float HealthPercent = 60.f;
};
