// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

class USoundCue;
class USTUWeaponFXComponent;

DECLARE_DELEGATE(FOnClipEmptySignature)

USTRUCT(BlueprintType)
struct FAmmoData {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0"))
	int32 Bullets = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0", EditCondition = "!Infinite"))
	int32 Clips = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool Infinite = false;
};

USTRUCT(BlueprintType)
struct FWeaponUIData {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UTexture2D> MainIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTexture2D* CrossHairIcon;
};

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor {
	GENERATED_BODY()

public:
	ASTUBaseWeapon();

	virtual void Destroyed() override;

	USTUWeaponFXComponent* GetVfx() const;
	const FWeaponUIData& GetUIData() const { return UIData; }
	const FAmmoData& GetAmmoData() const { return CurrentAmmo; }
	bool TryToAddAmmo(int32 ClipsAmount);

	bool CanReload() const;
	bool IsAmmoEmpty() const;
	bool IsAmmoFull() const;
	bool IsClipEmpty() const;

	void ChangeClip();
	void OnEquip() const;
	void StartFire();
	void StopFire();

	FOnClipEmptySignature OnClipEmpty;

protected:
	virtual void BeginPlay() override;
	virtual void MakeShotImpl();

	FTransform GetMuzzleTransform() const;
	AController* GetController() const;
	FHitResult GetHitResult() const;

	bool CheckEmptyClip() const;
	void MakeShot();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USTUWeaponFXComponent> FXComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundCue> ShotSound;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundCue> NoAmmoSound;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FWeaponUIData UIData;

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
	void GetShotTrace(FVector& Start, FVector& End) const;
	void TryToShot();

	FAmmoData CurrentAmmo;
	FTimerHandle FireTimer;
	bool bShotAccepted = false;
};
