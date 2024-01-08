// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STUFirearmWeapon.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUFirearmWeapon : public ASTUBaseWeapon {
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float ShotSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	int16 ShotDistance = 3000;

private:
	virtual FHitResult GetHitResult(const FVector& ViewLocation, const FRotator& ViewRotation) const override;
	virtual void MakeShot() override;
};
