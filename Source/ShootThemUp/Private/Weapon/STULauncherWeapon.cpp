// Shoot Them Up Game. All Rights Reserved.

#include "Weapon/STULauncherWeapon.h"

#include "Weapon/STUProjectile.h"

FHitResult ASTULauncherWeapon::GetHitResult(const FVector& ViewLocation, const FRotator& ViewRotation) const {
	return Super::GetHitResult(ViewLocation, ViewRotation);
}

void ASTULauncherWeapon::MakeShot() {
	auto* World = GetWorld();
	if (!World || !WeaponMesh) {
		return;
	}
	const auto SpawnTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	auto* Projectile = World->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform, this);
	Projectile->FinishSpawning(SpawnTransform);
}
