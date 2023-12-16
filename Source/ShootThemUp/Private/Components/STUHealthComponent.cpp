// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUHealthComponent.h"
#include "Dev/STUFireDamageType.h"
#include "Dev/STUIceDamageType.h"

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
	if (DamageType) {
		if (DamageType->IsA<USTUFireDamageType>()) {
			UE_LOG(HealthComponentLog, Display, TEXT("So HOT"));
		}
		else if (DamageType->IsA<USTUIceDamageType>()) {
			UE_LOG(HealthComponentLog, Display, TEXT("So COLD"));
		}
	}
}
