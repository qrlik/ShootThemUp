// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_NeedAmmo.generated.h"

class ASTUBaseWeapon;

UCLASS()
class SHOOTTHEMUP_API UBTDecorator_NeedAmmo : public UBTDecorator {
	GENERATED_BODY()
public:
	UBTDecorator_NeedAmmo();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASTUBaseWeapon> WeaponType;
};
