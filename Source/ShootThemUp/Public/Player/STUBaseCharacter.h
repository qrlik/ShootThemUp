// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

enum class EMatchState;
enum class EMovementFlags;
class USoundCue;
class USTUCharacterMovementComponent;
class USTUHealthComponent;
class USTUWeaponComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASTUBaseCharacter(const FObjectInitializer& Initializer);

	virtual void Reset() override;
	virtual void TurnOff() override;

	UFUNCTION(BlueprintCallable)
	float GetDirectionAngle() const;

	USTUHealthComponent* GetHealthComponent() const;
	USTUWeaponComponent* GetWeaponComponent() const;

	void SetPlayerColor(FLinearColor Color) const;

	void StartRun();
	void StopRun();

protected:
	virtual void BeginPlay() override;

	virtual void OnDeathImpl();
	virtual void OnHealthChangedImpl(float Delta) const;
	virtual void OnMatchStateChangedImpl(EMatchState State) const;

	void UpdateMovementFlag(EMovementFlags Flag, float Amount) const;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USTUHealthComponent> HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USTUWeaponComponent> WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundCue> DeathSound;

	UPROPERTY(EditDefaultsOnly, Category = "Material")
	FName TeamColorMaterial = "Paint Color";

	UPROPERTY(EditDefaultsOnly, Category = "Damage", meta = (ClampMin = "0.0"))
	FVector2D LandedDamageVelocity = FVector2D(600.f, 1500.f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage", meta = (ClampMin = "0.0"))
	FVector2D LandedDamage = FVector2D(10.f, 100.f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage", meta = (ClampMin = "0.0"))
	float LifeSpanOnDeath = 5.f;

private:
	void InitMatchStateDelegate();

	void OnDeath();
	void OnHealthChanged(float Delta) const;
	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
	void OnMatchStateChanged(EMatchState State);
};
