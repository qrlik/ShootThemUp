// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class ASTUBaseCharacter;
class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor {
	GENERATED_BODY()

public:
	ASTUBasePickup();

	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	bool IsActive() const;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundCue> PickupSound;

	UPROPERTY(EditAnywhere, Category = "Pickup", meta = (ClampMin = "0.0"))
	FVector2D MinMaxRotationSpeed = { 25.0, 75.0 };

	UPROPERTY(EditAnywhere, Category = "Pickup")
	float RespawnTime = 5.f;

	virtual bool GiveToImpl(ASTUBaseCharacter* Character) const;

private:
	bool GiveTo(TObjectPtr<APawn> Pawn) const;
	void GenerateRotationSpeed();
	void OnTake();
	void Respawn();
	void Rotate(float DeltaTime);
	void TryToGive();

	UPROPERTY()
	TArray<TObjectPtr<APawn>> Candidates;

	float DegreeRotationSpeed = 0.f;
	bool bActive = true;
};
