// Shoot Them Up Game. All Rights Reserved.

#include "Weapon/STUFirearmWeapon.h"
#include "Player/STUBaseCharacter.h"

FHitResult ASTUFirearmWeapon::GetHitResult(const FVector& ViewLocation, const FRotator& ViewRotation) const {
	FHitResult HitResult;
	const auto* World = GetWorld();
	if (!World) {
		return HitResult;
	}

	const auto HalfRad = FMath::DegreesToRadians(ShotSpread);
	const auto TraceRotation = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	const auto TraceEnd = ViewLocation + TraceRotation * ShotDistance;

	World->LineTraceSingleByChannel(HitResult, ViewLocation, TraceEnd, ECC_Visibility);
	return HitResult;
}

void ASTUFirearmWeapon::MakeShot() {
	const auto* World = GetWorld();
	const auto* Controller = GetController();
	if (!World || !Controller) {
		return;
	}

	FVector ViewLocation;
	FRotator ViewRotation;
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	if (const auto HitResult = GetHitResult(ViewLocation, ViewRotation); HitResult.bBlockingHit) {
		DrawDebugSphere(World, HitResult.ImpactPoint, 10.f, 24, FColor::Red, false, 5.f);

		if (auto* HitActor = HitResult.HitObjectHandle.FetchActor<ASTUBaseCharacter>()) {
			HitActor->TakeDamage(Damage, FDamageEvent{}, GetController(), this);
		}
	}
}


