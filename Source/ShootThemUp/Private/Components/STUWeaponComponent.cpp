// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUWeaponComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/STUBaseWeapon.h"

USTUWeaponComponent::USTUWeaponComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::Fire() {
	if (!CurrentWeapon) {
		return;
	}
	CurrentWeapon->Fire();
}

void USTUWeaponComponent::BeginPlay() {
	Super::BeginPlay();

	SpawnWeapon();
}

void USTUWeaponComponent::SpawnWeapon() {
	const auto Character = Cast<ACharacter>(GetOwner());
	const auto World = GetWorld();
	if (!Character || !World) {
		return;
	}

	CurrentWeapon = World->SpawnActor<ASTUBaseWeapon>(WeaponClass); // to do check destroy old weapon
	if (CurrentWeapon) {
		const auto AttachmentRules = FAttachmentTransformRules{ EAttachmentRule::SnapToTarget, false };
		CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachSocketName);
	}
}
