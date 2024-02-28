// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class ASTUBaseCharacter;
class ASTUBaseWeapon;
class UNiagaraComponent;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	ASTUProjectile();

	void SetWeaponOwner(AActor* Character);
	void SetDirection(const FVector& Value) { Direction = Value; }
	void SetDamageRadius(float Value) { DamageRadius = Value; }
	void SetDamage(float Value) { Damage = Value; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UNiagaraComponent> TraceComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> MovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UAudioComponent> AudioComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
	float LifeTime = 10.f;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	AController* GetController() const;

	void PlayHitEffect(const FHitResult& Hit) const;

	UPROPERTY()
	TObjectPtr<AActor> WeaponOwner;

	FVector Direction;
	float DamageRadius = 0.f;
	float Damage = 0.f;
};
