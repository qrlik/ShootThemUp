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
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(EditDefaultsOnly)
	float Cooldown = 0.1;

	UPROPERTY(EditDefaultsOnly)
	float Damage = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float BulletSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly)
	int16 TraceDistance = 3000;

private:
	FHitResult GetHitResult(FVector& Location, FRotator& Rotation) const;

	void MakeShot();

	AController* GetController() const;

	FTimerHandle FireTimer;
};
