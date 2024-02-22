// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STUBaseWidget.h"
#include "STUPlayerHUDWidget.generated.h"

class UProgressBar;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public USTUBaseWidget {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	FWeaponUIData GetCurrentWeaponUIData() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	FAmmoData GetCurrentWeaponAmmo() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	FString FormatBullets(int32 Bullets) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetKills() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerSpectating() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnTakeDamage();

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> DamageAnimation;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthProgressBar;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float PercentColorThreshold = 0.3f;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FLinearColor DefaultColor = FLinearColor::White;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FLinearColor LowColor = FLinearColor::Red;

private:
	void InitializeDamageEvent();

	void OnNewPawn();
	void OnHealthChanged(float Delta);

	void UpdateDamageAnimation();
	void UpdateHealthBar() const;
};
