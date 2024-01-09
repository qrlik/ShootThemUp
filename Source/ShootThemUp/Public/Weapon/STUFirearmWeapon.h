// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STUFirearmWeapon.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUFirearmWeapon : public ASTUBaseWeapon {
	GENERATED_BODY()

protected:
	virtual void MakeShot() override;
};
