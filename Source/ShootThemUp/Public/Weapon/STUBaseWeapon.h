// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor {
	GENERATED_BODY()

public:
	ASTUBaseWeapon();

	void StartFire();
	void StopFire();

protected:
	AController* GetController() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(EditDefaultsOnly)
	float Cooldown = 0.1;

	UPROPERTY(EditDefaultsOnly)
	float Damage = 10.f;

private:
	virtual FHitResult GetHitResult(const FVector& ViewLocation, const FRotator& ViewRotation) const;
	virtual void MakeShot();

	FTimerHandle FireTimer;
};
