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

	GenerateRotationSpeed();
}

void ASTUBasePickup::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	check(CollisionComponent);

	TryToGive();
	Rotate(DeltaTime);
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

void ASTUBasePickup::GenerateRotationSpeed() {
	const auto Direction = FMath::RandBool() ? 1 : -1;
	DegreeRotationSpeed = FMath::RandRange(MinMaxRotationSpeed.X, MinMaxRotationSpeed.Y) * Direction;
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
	GenerateRotationSpeed();
	bActive = true;
}

void ASTUBasePickup::Rotate(float DeltaTime) {
	const auto RotateDelta = DeltaTime / 1.0 * DegreeRotationSpeed;
	AddActorLocalRotation(FRotator{ 0.0, RotateDelta, 0.0 });
}
