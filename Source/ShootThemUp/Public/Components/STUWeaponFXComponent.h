// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponFXComponent.generated.h"

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
struct FHitEffect {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraSystem> NiagaraEffect;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundCue> Sound;
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
class SHOOTTHEMUP_API USTUWeaponFXComponent : public UActorComponent {
	GENERATED_BODY()

public:
	USTUWeaponFXComponent();

	void ShowTraceEffect(const FVector& TraceStart, const FVector& TraceEnd) const;
	void ShowMuzzleEffect(USceneComponent* Weapon, const FName& MuzzleSocket) const;
	void PlayHitEffect(const FHitResult& Hit) const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon Effects")
	TObjectPtr<UNiagaraSystem> MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Effects")
	FWeaponTrace Trace;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Effects")
	FHitEffect DefaultHitEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Effects")
	TMap<TObjectPtr<UPhysicalMaterial>, FHitEffect> HitEffectsMap;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Effects")
	FWeaponDecal HitDecal;
};
