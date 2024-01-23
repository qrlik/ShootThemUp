// Shoot Them Up Game. All Rights Reserved.

#include "Pickups/STUBasePickup.h"
#include "Components/SphereComponent.h"
#include "Components/STUHealthComponent.h"
#include "Player/STUBaseCharacter.h"

ASTUBasePickup::ASTUBasePickup() {
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	SetRootComponent(CollisionComponent);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComponent->SetupAttachment(CollisionComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASTUBasePickup::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	check(CollisionComponent);

	TryToGive();
}

void ASTUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor) {
	Super::NotifyActorBeginOverlap(OtherActor);

	if (auto* Pawn = Cast<APawn>(OtherActor)) {
		Candidates.AddUnique(Pawn);
	}
}

void ASTUBasePickup::NotifyActorEndOverlap(AActor* OtherActor) {
	Super::NotifyActorEndOverlap(OtherActor);

	Candidates.Remove(Cast<APawn>(OtherActor));
}

bool ASTUBasePickup::IsActive() const {
	return bActive;
}

bool ASTUBasePickup::GiveTo(TObjectPtr<APawn> Pawn) const {
	auto* Character = Cast<ASTUBaseCharacter>(Pawn);
	if (!Character) {
		return false;
	}
	if (const auto* HealthComponent = Character->GetHealthComponent(); HealthComponent && HealthComponent->IsDead()) {
		return false;
	}
	return GiveToImpl(Character);
}

bool ASTUBasePickup::GiveToImpl(ASTUBaseCharacter* Character) const {
	return false;
}

void ASTUBasePickup::TryToGive() {
	if (!IsActive()) {
		return;
	}
	for (const auto& Pawn : Candidates) {
		if (GiveTo(Pawn)) {
			OnTake();
			return;
		}
	}
}

void ASTUBasePickup::OnTake() {
	CollisionComponent->SetVisibility(false, true);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	bActive = false;

	FTimerHandle RespawnTimer;
	GetWorldTimerManager().SetTimer(RespawnTimer, this, &ASTUBasePickup::Respawn, RespawnTime);
}

void ASTUBasePickup::Respawn() {
	CollisionComponent->SetVisibility(true, true);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	bActive = true;
}
