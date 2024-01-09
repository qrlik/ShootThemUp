// Shoot Them Up Game. All Rights Reserved.

#include "Weapon/STUProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	SetRootComponent(CollisionComponent);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Block);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
}

void ASTUProjectile::BeginPlay() {
	Super::BeginPlay();

	MovementComponent->Velocity = Direction * MovementComponent->InitialSpeed;
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnHit);

	SetLifeSpan(LifeTime);
}

void ASTUProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
                           const FHitResult& Hit) {
	const auto* World = GetWorld();
	if (!World) {
		return;
	}

	MovementComponent->StopMovementImmediately();
	UGameplayStatics::ApplyRadialDamage(World, Damage, GetActorLocation(), DamageRadius, {}, {}, this, GetController(), false);
	DrawDebugSphere(World, GetActorLocation(), DamageRadius, 24, FColor::Red, false, LifeTime);

	Destroy();
}

AController* ASTUProjectile::GetController() const {
	const auto* Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}
