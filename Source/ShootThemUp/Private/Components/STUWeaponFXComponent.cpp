// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUWeaponFXComponent.h"

#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Sound/SoundCue.h"

USTUWeaponFXComponent::USTUWeaponFXComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponFXComponent::ShowTraceEffect(const FVector& TraceStart, const FVector& TraceEnd) const {
	if (auto* TraceComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Trace.TraceEffect, TraceStart)) {
		TraceComponent->SetVariableVec3(Trace.TraceVariableName, TraceEnd);
	}
}

void USTUWeaponFXComponent::PlayHitEffect(const FHitResult& Hit) const {
	auto HitEffect = DefaultHitEffect;

	if (Hit.PhysMaterial.IsValid()) {
		if (auto* Material = HitEffectsMap.Find(Hit.PhysMaterial.Get())) {
			HitEffect = *Material;
		}
	}

	UGameplayStatics::PlaySoundAtLocation(this, HitEffect.Sound, Hit.ImpactPoint);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, HitEffect.NiagaraEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	auto* Decal = UGameplayStatics::SpawnDecalAtLocation(this, HitDecal.Material, HitDecal.Size, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	if (Decal) {
		Decal->SetFadeOut(HitDecal.LifeTime, HitDecal.FadeOutTime);
	}
}

void USTUWeaponFXComponent::ShowMuzzleEffect(USceneComponent* Weapon, const FName& MuzzleSocket) const {
	UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleEffect, Weapon, MuzzleSocket, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget,
	                                             true);
}
