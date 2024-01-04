// Shoot Them Up Game. All Rights Reserved.

#include "GameFramework/Character.h"
#include "Weapon/STUBaseWeapon.h"

#include "Player/STUBaseCharacter.h"

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

AController* ASTUBaseWeapon::GetController() const {
	if (const auto* Character = Cast<ACharacter>(GetOwner())) {
		return Character->GetController();
	}
	return nullptr;
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

	FHitResult HitResult;
	const auto TraceEnd = ViewLocation + ViewRotation.Vector() * TraceDistance;
	World->LineTraceSingleByChannel(HitResult, ViewLocation, TraceEnd, ECC_Visibility);

	if (HitResult.bBlockingHit) {
		DrawDebugSphere(World, HitResult.ImpactPoint, 10.f, 24, FColor::Red, false, 5.f);
		if (auto* HitActor = HitResult.HitObjectHandle.FetchActor<ASTUBaseCharacter>()) {
			HitActor->TakeDamage(Damage, FDamageEvent{}, GetController(), this);
		}
	}
}
