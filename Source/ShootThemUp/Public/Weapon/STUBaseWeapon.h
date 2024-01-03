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

	virtual void Fire();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(EditDefaultsOnly)
	FName MuzzleSocket = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly)
	int16 TraceDistance = 1500;

private:
	void MakeShot();
};
