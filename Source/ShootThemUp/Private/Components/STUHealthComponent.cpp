// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(HealthComponentLog, All, All)

USTUHealthComponent::USTUHealthComponent() :
	Health(MaxHealth) {
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::BeginPlay() {
	Super::BeginPlay();
}

bool USTUHealthComponent::IsDead() const {
	return Health < 0.f || FMath::IsNearlyZero(Health);
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
                                          AActor* DamageCauser) {
	if (Damage < 0.f || FMath::IsNearlyZero(Damage) || IsDead()) {
		return;
	}
	Health -= Damage;

	if (IsDead()) {
		Health = 0.f;
		OnHealthChange.Execute();
		OnDeath.Broadcast();
	}
	else {
		OnHealthChange.Execute();
	}
}
