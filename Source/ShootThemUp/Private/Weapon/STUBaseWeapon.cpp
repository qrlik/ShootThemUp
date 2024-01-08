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

AController* ASTUBaseWeapon::GetController() const {
	if (const auto* Character = Cast<ACharacter>(GetOwner())) {
		return Character->GetController();
	}
	return nullptr;
}

FHitResult ASTUBaseWeapon::GetHitResult(const FVector& ViewLocation, const FRotator& ViewRotation) const {
	return FHitResult{};
}

void ASTUBaseWeapon::MakeShot() {
}
