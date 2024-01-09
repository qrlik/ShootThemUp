// Shoot Them Up Game. All Rights Reserved.

#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"

ASTUBaseWeapon::ASTUBaseWeapon() {
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void ASTUBaseWeapon::StartFire() {
	GetWorldTimerManager().SetTimer(FireTimer, this, &ASTUBaseWeapon::MakeShot, Cooldown, true, 0.f);

	//GetWorldTimerManager().SetTimer(
	//	FireTimer,
	//	[ptr = TWeakObjectPtr<ASTUBaseWeapon>(this)]() {
	//		if (ptr.IsValid()) {
	//			ptr->MakeShot();
	//		}
	//	},
	//	Cooldown, true, 0.f);
}

void ASTUBaseWeapon::StopFire() {
	GetWorldTimerManager().ClearTimer(FireTimer);
}

FTransform ASTUBaseWeapon::GetMuzzleTransform() const {
	if (WeaponMesh) {
		return WeaponMesh->GetSocketTransform(MuzzleSocketName);
	}
	return FTransform{};
}

AController* ASTUBaseWeapon::GetController() const {
	if (const auto* Character = Cast<ACharacter>(GetOwner())) {
		return Character->GetController();
	}
	return nullptr;
}

FHitResult ASTUBaseWeapon::GetHitResult() const {
	FHitResult HitResult;
	FVector TraceStart, TraceEnd;
	GetShotTrace(TraceStart, TraceEnd);

	if (const auto* World = GetWorld()) {
		World->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility);
	}
	if (!HitResult.bBlockingHit) {
		HitResult.ImpactPoint = TraceEnd;
	}
	return HitResult;
}

void ASTUBaseWeapon::GetShotTrace(FVector& Start, FVector& End) const {
	const auto* Controller = GetController();
	if (!Controller) {
		return;
	}

	FRotator ViewRotation;
	Controller->GetPlayerViewPoint(Start, ViewRotation);

	const auto HalfRad = FMath::DegreesToRadians(ShotSpread);
	const auto TraceRotation = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	End = Start + TraceRotation * ShotDistance;
}

void ASTUBaseWeapon::MakeShot() {
}
