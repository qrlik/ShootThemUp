// Shoot Them Up Game. All Rights Reserved.

#include "GameFramework/Character.h"
#include "Weapon/STUBaseWeapon.h"

#include "Player/STUBaseCharacter.h"

ASTUBaseWeapon::ASTUBaseWeapon() {
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void ASTUBaseWeapon::StartFire() {
	GetWorldTimerManager().SetTimer(FireTimer, this, &ASTUBaseWeapon::MakeShot, Cooldown, true, 0.f);
}

void ASTUBaseWeapon::StopFire() {
	GetWorldTimerManager().ClearTimer(FireTimer);
}

void ASTUBaseWeapon::BeginPlay() {
	Super::BeginPlay();
}

AController* ASTUBaseWeapon::GetController() const {
	if (const auto* Character = Cast<ACharacter>(GetOwner())) {
		return Character->GetController();
	}
	return nullptr;
}

FHitResult ASTUBaseWeapon::GetHitResult(FVector& ViewLocation, FRotator& ViewRotation) const {
	FHitResult HitResult;
	const auto* World = GetWorld();
	if (!World) {
		return HitResult;
	}

	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const auto TraceRotation = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	const auto TraceEnd = ViewLocation + TraceRotation * TraceDistance;

	World->LineTraceSingleByChannel(HitResult, ViewLocation, TraceEnd, ECC_Visibility);
	return HitResult;
}

void ASTUBaseWeapon::MakeShot() {
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
