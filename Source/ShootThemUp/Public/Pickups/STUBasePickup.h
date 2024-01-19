// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

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
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	float RespawnTime = 5.f;

	virtual bool GiveTo(TObjectPtr<APawn> Pawn) const;

private:
	void TryToGive();
	void OnTake();
	void Respawn();

	UPROPERTY()
	TArray<TObjectPtr<APawn>> Candidates;

	bool bActive = true;
};
