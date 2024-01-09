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
	virtual void MakeShot();

	FTransform GetMuzzleTransform() const;
	AController* GetController() const;
	FHitResult GetHitResult() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float Cooldown = 0.1;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float Damage = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float ShotSpread = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	int16 ShotDistance = 3000;

private:
	void GetShotTrace(FVector& Start, FVector& End) const;

	FTimerHandle FireTimer;
};
