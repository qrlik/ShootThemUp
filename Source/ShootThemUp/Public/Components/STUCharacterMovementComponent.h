// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STUCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	virtual float GetMaxSpeed() const override;

	// calculate factor for velocity state
	// 0 - stay, (0, 1] - walk, (1, 2] - run
	UFUNCTION(BlueprintCallable)
	float GetVelocityFactor() const;

	void SetCanRun(bool State) { CanRun = State; }

protected:
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "1.0"), Category = "Character Movement: Walking")
	float RunModifier = 2.f;

private:
	bool CanRun = false;
};
