// Shoot Them Up Game. All Rights Reserved.


#include "Components/STUCharacterMovementComponent.h"

void USTUCharacterMovementComponent::AddMovementFlag(EMovementFlags Flag) {
	MovementFlags |= Flag;
}

void USTUCharacterMovementComponent::RemoveMovementFlag(EMovementFlags Flag) {
	MovementFlags &= ~Flag;
}

float USTUCharacterMovementComponent::GetMaxSpeed() const {
	return (MovementFlags == EMovementFlags::AbleToRun) ? Super::GetMaxSpeed() * RunModifier : Super::GetMaxSpeed();
}

float USTUCharacterMovementComponent::GetVelocityFactor() const {
	const auto DefaultMaxSpeed = Super::GetMaxSpeed();
	const auto VelocityLength = Velocity.Length();

	if (VelocityLength <= DefaultMaxSpeed) {
		return VelocityLength / DefaultMaxSpeed;
	}

	if (const float RunDelta = DefaultMaxSpeed * RunModifier - DefaultMaxSpeed; RunDelta > 0.0) {
		const float Delta = VelocityLength - DefaultMaxSpeed;
		return 1.0 + Delta / RunDelta;
	}

	return VelocityLength / DefaultMaxSpeed;
}
