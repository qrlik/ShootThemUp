// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ChangeWeaponService.generated.h"

UCLASS()
class SHOOTTHEMUP_API UChangeWeaponService : public UBTService {
	GENERATED_BODY()

public:
	UChangeWeaponService();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float Probability = 0.5f;

private:
	void TryToChangeWeapon(UBehaviorTreeComponent& OwnerComp) const;
	bool RollWeaponChange() const;
};
