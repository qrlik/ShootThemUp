// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

DECLARE_DELEGATE(FOnClipEmptySignature)

USTRUCT(BlueprintType)
struct FAmmoData {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (ClampMin = "0"))
	int32 Bullets = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (ClampMin = "0", EditCondition = "!Infinite"))
	int32 Clips = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	bool Infinite = false;
};

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor {
	GENERATED_BODY()

public:
	ASTUBaseWeapon();

	virtual void Destroyed() override;

	bool CanReload() const;

	void ChangeClip();
	void StartFire();
	void StopFire();

	FOnClipEmptySignature OnClipEmpty;

protected:
	virtual void BeginPlay() override;
	virtual void MakeShotImpl();

	FTransform GetMuzzleTransform() const;
	AController* GetController() const;
	FHitResult GetHitResult() const;

	bool IsAmmoEmpty() const;
	bool IsClipEmpty() const;

	void MakeShot();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FAmmoData DefaultAmmo;

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
	void DecreaseAmmo();
	void LogAmmo() const;

	void GetShotTrace(FVector& Start, FVector& End) const;
	void TryToShot();

	FAmmoData CurrentAmmo;
	FTimerHandle FireTimer;
	bool bShotAccepted = false;
};
