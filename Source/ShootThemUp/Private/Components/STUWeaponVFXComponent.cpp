// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUWeaponVFXComponent.h"

#include "NiagaraFunctionLibrary.h"

USTUWeaponVFXComponent::USTUWeaponVFXComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponVFXComponent::PlayHitEffect(const FHitResult& Hit) const {
	auto HitEffect = DefaultHitEffect;

	if (Hit.PhysMaterial.IsValid()) {
		if (auto* Material = HitEffectsMap.Find(Hit.PhysMaterial.Get())) {
			HitEffect = *Material;
		}
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}
