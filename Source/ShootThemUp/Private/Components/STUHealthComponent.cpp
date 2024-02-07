// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(HealthComponentLog, All, All)

USTUHealthComponent::USTUHealthComponent() :
	Health(MaxHealth) {
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::BeginPlay() {
	Super::BeginPlay();
	check(MaxHealth > 0.f);
}

int USTUHealthComponent::GetHealthPercent() const {
	return static_cast<int>(Health / MaxHealth * 100);
}

bool USTUHealthComponent::IsDead() const {
	return Health < 0.f || FMath::IsNearlyZero(Health);
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
                                          AActor* DamageCauser) {
	if (Damage < 0.f || FMath::IsNearlyZero(Damage) || IsDead()) {
		return;
	}
	AddHealth(-Damage);
	if (const auto World = GetWorld()) {
		World->GetTimerManager().ClearTimer(AutoHealTimer);
	}

	if (IsDead()) {
		OnDeath.Broadcast();
	}
	else {
		StartAutoHeal();
	}
}

bool USTUHealthComponent::IsFullHealth() const {
	return FMath::IsNearlyEqual(Health, MaxHealth) || Health > MaxHealth;
}

bool USTUHealthComponent::TryToAddHealth(float HealthAmount) {
	if (IsFullHealth() || IsDead()) {
		return false;
	}
	AddHealth(HealthAmount);
	return true;
}

void USTUHealthComponent::AddHealth(float Delta) {
	Health = FMath::Clamp(Health + Delta, 0.f, MaxHealth);
	OnHealthChange.Broadcast(Delta);
}

void USTUHealthComponent::AddAutoHealTick() {
	AddHealth(AutoHealTick);
	if (FMath::IsNearlyEqual(Health, MaxHealth)) {
		if (const auto World = GetWorld()) {
			World->GetTimerManager().ClearTimer(AutoHealTimer);
		}
	}
}

void USTUHealthComponent::StartAutoHeal() {
	if (!AutoHeal) {
		return;
	}
	if (const auto World = GetWorld()) {
		World->GetTimerManager().SetTimer(AutoHealTimer, this, &USTUHealthComponent::AddAutoHealTick, AutoHealFrequency, true, AutoHealDelay);
	}
}
