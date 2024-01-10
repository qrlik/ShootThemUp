// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent {
	GENERATED_BODY()

public:
	USTUWeaponComponent();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void NextWeapon();
	void StartFire();
	void StopFire();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<TSubclassOf<ASTUBaseWeapon>> WeaponClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName EquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName ArmorySocketName = "ArmorySocket";

private:
	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, const FName& SocketName) const;
	void EquipWeapon(int32 Index);
	void SpawnWeapons();

	UPROPERTY()
	TArray<TObjectPtr<ASTUBaseWeapon>> Weapons;
	UPROPERTY()
	TObjectPtr<ASTUBaseWeapon> CurrentWeapon;

	int32 CurrentWeaponIndex = 0;
};
