// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent {
	GENERATED_BODY()

public:
	USTUHealthComponent();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	float GetHealth() const { return Health; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0.0"))
	float MaxHealth = 100.f;

private:
	float Health = 0.f;

};
