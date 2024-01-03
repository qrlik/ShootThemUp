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

void ASTUBaseWeapon::MakeShot() {
	const auto World = GetWorld();
	if (!World) {
		return;
	}

	const auto* Character = Cast<ACharacter>(GetOwner());
	const auto* Controller = Character->GetController();

	// to do check + refactor

	auto ViewRotation = Character->GetBaseAimRotation();
	const auto SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocket);

	const auto TraceStart = SocketTransform.GetLocation();
	const auto ShootDirection = ViewRotation.Vector(); // SocketTransform.GetRotation().GetForwardVector();
	const auto TraceEnd = TraceStart + ShootDirection * TraceDistance;

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	if (World->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionParams)) {
		DrawDebugSphere(World, HitResult.ImpactPoint, 10.f, 24, FColor::Red, false, 5.f);
		DrawDebugLine(World, TraceStart, HitResult.ImpactPoint, FColor::Red, false, 3.f, 0, 2.f);
	}
	else {
		DrawDebugLine(World, TraceStart, TraceEnd, FColor::Red, false, 3.f, 0, 2.f);
	}
}
