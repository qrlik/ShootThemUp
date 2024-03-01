// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STUFirearmWeapon.generated.h"

class UPhysicalMaterial;

UCLASS()
class SHOOTTHEMUP_API ASTUFirearmWeapon : public ASTUBaseWeapon {
	GENERATED_BODY()

protected:
	virtual void MakeShotImpl() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TMap<TObjectPtr<UPhysicalMaterial>, float> DamageModifiers;

private:
	float CalculateDamage(const FHitResult& Hit) const;
};
