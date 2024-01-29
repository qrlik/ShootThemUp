// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUWeaponVFXComponent.h"

#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

USTUWeaponVFXComponent::USTUWeaponVFXComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponVFXComponent::ShowTraceEffect(const FVector& TraceStart, const FVector& TraceEnd) const {
	if (auto* TraceComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Trace.TraceEffect, TraceStart)) {
		TraceComponent->SetVariableVec3(Trace.TraceVariableName, TraceEnd);
	}
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

void USTUWeaponVFXComponent::ShowMuzzleEffect(USceneComponent* Weapon, const FName& MuzzleSocket) const {
	UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleEffect, Weapon, MuzzleSocket, FVector::ZeroVector,
	                                             FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
}
