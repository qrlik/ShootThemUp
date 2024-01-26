// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STUFirearmWeapon.generated.h"

class USTUFXComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUFirearmWeapon : public ASTUBaseWeapon {
	GENERATED_BODY()

public:
	ASTUFirearmWeapon();

protected:
	virtual void BeginPlay() override;
	virtual void MakeShotImpl() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USTUFXComponent> FXComponent;
};
