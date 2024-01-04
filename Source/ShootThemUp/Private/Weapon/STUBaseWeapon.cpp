// Shoot Them Up Game. All Rights Reserved.

#include "GameFramework/Character.h"
#include "Weapon/STUBaseWeapon.h"

ASTUBaseWeapon::ASTUBaseWeapon() {
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void ASTUBaseWeapon::Fire() {
	MakeShot();
}

void ASTUBaseWeapon::BeginPlay() {
	Super::BeginPlay();
}

bool ASTUBaseWeapon::GetViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const {
	if (const auto* Character = Cast<ACharacter>(GetOwner())) {
		if (const auto* Controller = Character->GetController()) {
			Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
			return true;
		}
	}
	return false;
}

void ASTUBaseWeapon::MakeShot() const {
	const auto* World = GetWorld();
	if (!World) {
		return;
	}

	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetViewPoint(ViewLocation, ViewRotation)) {
		return;
	}

	FHitResult HitResult;
	const auto TraceEnd = ViewLocation + ViewRotation.Vector() * TraceDistance;
	World->LineTraceSingleByChannel(HitResult, ViewLocation, TraceEnd, ECC_Visibility);

	if (HitResult.bBlockingHit) {
		DrawDebugSphere(World, HitResult.ImpactPoint, 10.f, 24, FColor::Red, false, 5.f);
	}
}
