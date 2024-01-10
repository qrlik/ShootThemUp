// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUWeaponComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/STUBaseWeapon.h"

USTUWeaponComponent::USTUWeaponComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	CurrentWeapon = nullptr;
	for (const auto Weapon : Weapons) {
		Weapon->StopFire();
		Weapon->Destroy();
	}
	Weapons.Empty();

	Super::EndPlay(EndPlayReason);
}

void USTUWeaponComponent::NextWeapon() {
	const auto NextWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(NextWeaponIndex);
}

void USTUWeaponComponent::StartFire() {
	if (CurrentWeapon) {
		CurrentWeapon->StartFire();
	}
}

void USTUWeaponComponent::StopFire() {
	if (CurrentWeapon) {
		CurrentWeapon->StopFire();
	}
}

void USTUWeaponComponent::BeginPlay() {
	Super::BeginPlay();

	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon* Weapon, const FName& SocketName) const {
	const auto* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !Weapon) {
		return;
	}
	const auto AttachmentRules = FAttachmentTransformRules{ EAttachmentRule::SnapToTarget, false };
	Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, SocketName);
}

void USTUWeaponComponent::EquipWeapon(int32 Index) {
	if (Index >= Weapons.Num()) {
		return;
	}
	const auto WeaponToEquip = Weapons[Index];
	if (WeaponToEquip == CurrentWeapon) {
		return;
	}
	if (CurrentWeapon) {
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, ArmorySocketName);
	}
	CurrentWeaponIndex = Index;
	CurrentWeapon = WeaponToEquip;
	AttachWeaponToSocket(CurrentWeapon, EquipSocketName);
}

void USTUWeaponComponent::SpawnWeapons() {
	const auto World = GetWorld();
	if (!World) {
		return;
	}

	for (auto WeaponClass : WeaponClasses) {
		auto* Weapon = World->SpawnActor<ASTUBaseWeapon>(WeaponClass);
		if (!Weapon) {
			continue;
		}
		Weapon->SetOwner(GetOwner());
		Weapons.Add(Weapon);
		AttachWeaponToSocket(Weapon, ArmorySocketName);
	}
}
