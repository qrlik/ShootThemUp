// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(HealthComponentLog, All, All)

USTUHealthComponent::USTUHealthComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::BeginPlay() {
	Super::BeginPlay();
	Health = MaxHealth;
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
                                          AActor* DamageCauser) {
	Health -= Damage;
}
