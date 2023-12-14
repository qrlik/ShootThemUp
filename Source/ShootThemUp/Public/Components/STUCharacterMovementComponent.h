// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STUCharacterMovementComponent.generated.h"

enum class EMovementFlags {
	None = 0,
	MoveForward = (1 << 0),
	MoveSide = (1 << 1),
	AllowToRun = (1 << 2),
	AbleToRun = MoveForward | AllowToRun
};

ENUM_CLASS_FLAGS(EMovementFlags)

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

	void AddMovementFlag(EMovementFlags Flag);
	void RemoveMovementFlag(EMovementFlags Flag);

protected :
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "1.0"), Category = "Character Movement: Walking")
	float RunModifier = 2.f;

private:
	EMovementFlags MovementFlags = EMovementFlags::None;
};
