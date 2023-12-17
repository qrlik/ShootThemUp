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

	if (const float RunDelta = GetMaxSpeed() - DefaultMaxSpeed; RunDelta > 0.0) {
		const float Delta = VelocityLength - DefaultMaxSpeed;
		return 1.0 + Delta / RunDelta;
	}

	return VelocityLength / DefaultMaxSpeed;
}

float USTUCharacterMovementComponent::GetLandedDamage() const {
	const auto FallVelocity = -Velocity.Z;
	if (FallVelocity < 0.f || FallVelocity < LandedDamageVelocity.X) {
		return 0.f;
	}
	return FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocity);
}