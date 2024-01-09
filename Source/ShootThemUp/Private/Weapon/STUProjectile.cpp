// Shoot Them Up Game. All Rights Reserved.

#include "Weapon/STUProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	SetRootComponent(CollisionComponent);
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
}

void ASTUProjectile::BeginPlay() {
	Super::BeginPlay();

	MovementComponent->Velocity = Direction * MovementComponent->InitialSpeed;
	SetLifeSpan(LifeTime);
}
