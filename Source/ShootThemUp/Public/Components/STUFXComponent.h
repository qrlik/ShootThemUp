// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUFXComponent.generated.h"

class UNiagaraSystem;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUFXComponent : public UActorComponent {
	GENERATED_BODY()

public:
	USTUFXComponent();

	void PlayImpactFX(const FHitResult& Hit) const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FX")
	TObjectPtr<UNiagaraSystem> Effect;
};
