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

void USTUWeaponComponent::OnEquipFinished() {
	bEquipInProgress = false;
}

void USTUWeaponComponent::OnFire(float Amount) {
	if (FMath::IsNearlyZero(Amount)) {
		StopFire();
	}
	else {
		StartFire();
	}
}

void USTUWeaponComponent::NextWeapon() {
	if (!CanEquip()) {
		return;
	}
	const auto NextWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(NextWeaponIndex);
}

void USTUWeaponComponent::Reload() {
	const auto CurrentData = WeaponData.FindByPredicate([Weapon = CurrentWeapon](const FWeaponData& Data) {
		return Weapon.GetClass() == Data.WeaponClass;
	});
	if (CurrentData) {
		PlayAnimMontage(CurrentData->ReloadAnimMontage);
	}
}

void USTUWeaponComponent::StartFire() {
	if (CanFire()) {
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

bool USTUWeaponComponent::CanFire() const {
	return CurrentWeapon && !bEquipInProgress;
}

bool USTUWeaponComponent::CanEquip() const {
	return !bEquipInProgress;
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
	if (Index < 0 && Index >= Weapons.Num()) {
		return;
	}
	const auto WeaponToEquip = Weapons[Index];
	if (WeaponToEquip == CurrentWeapon) {
		return;
	}
	if (CurrentWeapon) {
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, ArmorySocketName);
		PlayAnimMontage(EquipAnimMontage);
		bEquipInProgress = true;
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

	for (const auto& Data : WeaponData) {
		auto* Weapon = World->SpawnActor<ASTUBaseWeapon>(Data.WeaponClass);
		if (!Weapon) {
			continue;
		}
		Weapon->SetOwner(GetOwner());
		Weapons.Add(Weapon);
		AttachWeaponToSocket(Weapon, ArmorySocketName);
	}
}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* AnimMontage) const {
	auto* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !AnimMontage) {
		return;
	}
	Character->PlayAnimMontage(AnimMontage);
}
