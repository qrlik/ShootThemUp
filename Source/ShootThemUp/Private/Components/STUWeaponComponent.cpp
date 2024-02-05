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
	if (CurrentWeapon) {
		CurrentWeapon->OnEquip();
	}
}

void USTUWeaponComponent::OnReloadFinished() {
	bReloadInProgress = false;
	if (CurrentWeapon) {
		CurrentWeapon->ChangeClip();
	}
	OnReloadFinishedImpl();
}

FAmmoData USTUWeaponComponent::GetAmmoData() const {
	if (CurrentWeapon) {
		return CurrentWeapon->GetAmmoData();
	}
	return {};
}

FWeaponUIData USTUWeaponComponent::GetUIData() const {
	if (CurrentWeapon) {
		return CurrentWeapon->GetUIData();
	}
	return {};
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
	if (!CanDoAction()) {
		return;
	}
	EquipWeapon(GetNextWeaponIndex());
}

void USTUWeaponComponent::Reload() {
	if (!CanDoAction() || !CurrentWeapon || !CurrentWeapon->CanReload()) {
		return;
	}
	const auto CurrentData = WeaponData.FindByPredicate([Weapon = CurrentWeapon](const FWeaponData& Data) { return Weapon.GetClass() == Data.WeaponClass; });
	if (CurrentData) {
		PlayAnimMontage(CurrentData->ReloadAnimMontage);
		bReloadInProgress = true;
	}
}

bool USTUWeaponComponent::TryToAddAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType, int32 ClipsAmount) const {
	for (const auto& Weapon : Weapons) {
		if (Weapon && Weapon->IsA(WeaponType)) {
			return Weapon->TryToAddAmmo(ClipsAmount);
		}
	}
	return false;
}

bool USTUWeaponComponent::IsNextWeaponCanFire() const {
	if (const auto* NextWeapon = GetNextWeapon()) {
		return !NextWeapon->IsAmmoEmpty();
	}
	return false;
}

void USTUWeaponComponent::StartFire() {
	if (!CurrentWeapon) {
		return;
	}
	if (CanDoAction()) {
		CurrentWeapon->StartFire();
	}
	else {
		CurrentWeapon->StopFire();
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

void USTUWeaponComponent::OnEmptyClipImpl() {
}

void USTUWeaponComponent::OnReloadFinishedImpl() {
}

ASTUBaseWeapon* USTUWeaponComponent::GetCurrentWeapon() const {
	return CurrentWeapon;
}

ASTUBaseWeapon* USTUWeaponComponent::GetNextWeapon() const {
	const auto NextIndex = GetNextWeaponIndex();
	if (NextIndex < 0 && NextIndex >= Weapons.Num()) {
		return CurrentWeapon;
	}
	return Weapons[NextIndex];
}

bool USTUWeaponComponent::CanDoAction() const {
	return !bEquipInProgress && !bReloadInProgress;
}

void USTUWeaponComponent::OnEmptyClip(TSubclassOf<ASTUBaseWeapon> WeaponClass) {
	if (CurrentWeapon && WeaponClass == CurrentWeapon.GetClass()) {
		Reload();
		OnEmptyClipImpl();
	}
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
		Weapon->OnClipEmpty.BindUObject(this, &USTUWeaponComponent::OnEmptyClip, Data.WeaponClass);
		Weapons.Add(Weapon);
		AttachWeaponToSocket(Weapon, ArmorySocketName);
	}
}

int32 USTUWeaponComponent::GetNextWeaponIndex() const {
	return (CurrentWeaponIndex + 1) % Weapons.Num();
}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* AnimMontage) const {
	auto* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !AnimMontage) {
		return;
	}
	Character->PlayAnimMontage(AnimMontage);
}
