// Shoot Them Up Game. All Rights Reserved.

#include "Weapon/STULauncherWeapon.h"

#include "Components/STUWeaponFXComponent.h"
#include "Weapon/STUProjectile.h"

void ASTULauncherWeapon::MakeShotImpl() {
	auto* World = GetWorld();
	if (!World) {
		return;
	}

	const auto SpawnTransform = GetMuzzleTransform();
	if (auto* Projectile = World->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform, this)) {
		const auto HitResult = GetHitResult();
		const auto& TraceEnd = (HitResult.bBlockingHit) ? HitResult.ImpactPoint : HitResult.TraceEnd;
		const auto Direction = (TraceEnd - SpawnTransform.GetLocation()).GetSafeNormal();

		Projectile->SetWeaponOwner(GetOwner());
		Projectile->SetDirection(Direction);
		Projectile->SetDamageRadius(DamageRadius);
		Projectile->SetDamage(Damage);

		Projectile->FinishSpawning(SpawnTransform);
	}
}
