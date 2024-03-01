// Shoot Them Up Game. All Rights Reserved.

#include "Weapon/STUFirearmWeapon.h"

#include "Components/STUWeaponFXComponent.h"
#include "Player/STUBaseCharacter.h"
#include "STUUtils.h"

void ASTUFirearmWeapon::MakeShotImpl() {
	const auto* World = GetWorld();
	if (!World) {
		return;
	}

	const auto HitResult = GetHitResult();
	const auto& TraceEnd = (HitResult.bBlockingHit) ? HitResult.ImpactPoint : HitResult.TraceEnd;
	FXComponent->ShowTraceEffect(GetMuzzleTransform().GetLocation(), TraceEnd);
	if (HitResult.bBlockingHit) {
		//DrawDebugSphere(World, HitResult.ImpactPoint, 10.f, 24, FColor::Red, false, 5.f);
		FXComponent->PlayHitEffect(HitResult);

		if (auto* HitActor = HitResult.HitObjectHandle.FetchActor<ASTUBaseCharacter>()) {
			HitActor->TakeDamage(CalculateDamage(HitResult), FDamageEvent{}, STUUtils::GetController(GetOwner()), this);
		}
	}
}

float ASTUFirearmWeapon::CalculateDamage(const FHitResult& Hit) const {
	if (Hit.PhysMaterial.IsValid()) {
		if (const auto* Modifier = DamageModifiers.Find(Hit.PhysMaterial.Get())) {
			return *Modifier * Damage;
		}
	}
	return Damage;
}
