// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUWeaponVFXComponent.h"

#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"

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
	auto* Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), HitDecal.Material, HitDecal.Size, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	if (Decal) {
		Decal->SetFadeOut(HitDecal.LifeTime, HitDecal.FadeOutTime);
	}
}
