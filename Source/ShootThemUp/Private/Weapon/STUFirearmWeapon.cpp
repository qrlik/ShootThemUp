// Shoot Them Up Game. All Rights Reserved.

#include "Weapon/STUFirearmWeapon.h"

#include "Components/STUWeaponVFXComponent.h"
#include "Player/STUBaseCharacter.h"

void ASTUFirearmWeapon::MakeShotImpl() {
	const auto* World = GetWorld();
	if (!World) {
		return;
	}

	if (const auto HitResult = GetHitResult(); HitResult.bBlockingHit) {
		//DrawDebugSphere(World, HitResult.ImpactPoint, 10.f, 24, FColor::Red, false, 5.f);
		Vfx->PlayHitEffect(HitResult);

		if (auto* HitActor = HitResult.HitObjectHandle.FetchActor<ASTUBaseCharacter>()) {
			HitActor->TakeDamage(Damage, FDamageEvent{}, GetController(), this);
		}
	}
}


