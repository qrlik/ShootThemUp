// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "STUWeaponComponent.generated.h"

USTRUCT(BlueprintType)
struct FWeaponData {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASTUBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TObjectPtr<UAnimMontage> ReloadAnimMontage;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent {
	GENERATED_BODY()

public:
	USTUWeaponComponent();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable)
	void OnEquipFinished();
	UFUNCTION(BlueprintCallable)
	void OnReloadFinished();

	FAmmoData GetAmmoData() const;
	FWeaponUIData GetUIData() const;
	bool TryToAddAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType, int32 ClipsAmount) const;
	void OnFire(float Amount);
	void NextWeapon();
	void Reload();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TObjectPtr<UAnimMontage> EquipAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName EquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName ArmorySocketName = "ArmorySocket";

private:
	bool CanDoAction() const;

	void OnEmptyClip(TSubclassOf<ASTUBaseWeapon> WeaponClass);

	void StartFire();
	void StopFire();

	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, const FName& SocketName) const;
	void EquipWeapon(int32 Index);
	void SpawnWeapons();

	void PlayAnimMontage(UAnimMontage* AnimMontage) const;

	UPROPERTY()
	TArray<TObjectPtr<ASTUBaseWeapon>> Weapons;
	UPROPERTY()
	TObjectPtr<ASTUBaseWeapon> CurrentWeapon;

	int32 CurrentWeaponIndex = 0;
	bool bEquipInProgress = false;
	bool bReloadInProgress = false;
};
