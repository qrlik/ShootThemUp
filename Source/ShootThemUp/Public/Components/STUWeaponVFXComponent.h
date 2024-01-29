// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponVFXComponent.generated.h"

class UNiagaraComponent;
class UPhysicalMaterial;
class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FWeaponDecal {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterialInterface> Material;

	UPROPERTY(EditDefaultsOnly)
	FVector Size;

	UPROPERTY(EditDefaultsOnly)
	float LifeTime = 0.f;

	UPROPERTY(EditDefaultsOnly)
	float FadeOutTime = 0.f;
};

USTRUCT(BlueprintType)
struct FWeaponTrace {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraSystem> TraceEffect;

	UPROPERTY(EditDefaultsOnly)
	FName TraceVariableName = "TraceEnd";
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponVFXComponent : public UActorComponent {
	GENERATED_BODY()

public:
	USTUWeaponVFXComponent();

	void ShowTraceEffect(const FVector& TraceStart, const FVector& TraceEnd) const;
	void ShowMuzzleEffect(USceneComponent* Weapon, const FName& MuzzleSocket) const;
	void PlayHitEffect(const FHitResult& Hit) const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	TObjectPtr<UNiagaraSystem> MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	FWeaponTrace Trace;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	TObjectPtr<UNiagaraSystem> DefaultHitEffect;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	TMap<TObjectPtr<UPhysicalMaterial>, TObjectPtr<UNiagaraSystem>> HitEffectsMap;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	FWeaponDecal HitDecal;
};
