// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUFXComponent.h"

#include "NiagaraFunctionLibrary.h"

USTUFXComponent::USTUFXComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUFXComponent::PlayImpactFX(const FHitResult& Hit) const {
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}
