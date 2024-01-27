// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponVFXComponent.generated.h"

class UPhysicalMaterial;
class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FWeaponDecal {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UMaterialInterface> Material;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector Size;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float LifeTime = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float FadeOutTime = 0.f;
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponVFXComponent : public UActorComponent {
	GENERATED_BODY()

public:
	USTUWeaponVFXComponent();

	void PlayHitEffect(const FHitResult& Hit) const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TObjectPtr<UNiagaraSystem> DefaultHitEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TMap<TObjectPtr<UPhysicalMaterial>, TObjectPtr<UNiagaraSystem>> HitEffectsMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FWeaponDecal HitDecal;
};
