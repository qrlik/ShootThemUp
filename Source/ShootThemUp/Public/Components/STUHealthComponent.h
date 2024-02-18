// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangeSignature, float);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent {
	GENERATED_BODY()

public:
	USTUHealthComponent();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Health")
	int GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealth() const { return Health; }

	UFUNCTION()
	bool IsDead() const;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	bool IsFullHealth() const;
	bool TryToAddHealth(float HealthAmount);

	FOnHealthChangeSignature OnHealthChange;
	FOnDeathSignature OnDeath;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "1.0"), Category = "Health")
	float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	bool AutoHeal = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0.0", EditCondition = "AutoHeal"), Category = "Health")
	float AutoHealDelay = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0.0", EditCondition = "AutoHeal"), Category = "Health")
	float AutoHealTick = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0.0", EditCondition = "AutoHeal"), Category = "Health")
	float AutoHealFrequency = 1.f;

private:
	void AddHealth(float Delta);

	void AddAutoHealTick();
	void StartAutoHeal();

	void Killed(const AController* Killer) const;

	FTimerHandle AutoHealTimer;

	float Health = 0.f;
};
