// Shoot Them Up Game. All Rights Reserved.

#include "Weapon/STULauncherWeapon.h"
#include "Weapon/STUProjectile.h"

void ASTULauncherWeapon::MakeShot() {
	auto* World = GetWorld();
	if (!World) {
		return;
	}

	const auto SpawnTransform = GetMuzzleTransform();
	if (auto* Projectile = World->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform, GetOwner())) {
		const auto HitResult = GetHitResult();
		const auto Direction = (HitResult.ImpactPoint - SpawnTransform.GetLocation()).GetSafeNormal();

		Projectile->SetDirection(Direction);
		Projectile->SetDamageRadius(DamageRadius);
		Projectile->SetDamage(Damage);

		Projectile->FinishSpawning(SpawnTransform);
	}
}
