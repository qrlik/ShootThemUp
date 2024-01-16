// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Weapon/STUBaseWeapon.h"
#include "STUPlayerHUDWidget.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FWeaponUIData GetCurrentWeaponUIData() const;

	UFUNCTION(BlueprintCallable)
	FAmmoData GetCurrentWeaponAmmo() const;

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable)
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable)
	bool IsPlayerSpectating() const;
};
