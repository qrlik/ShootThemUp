// Shoot Them Up Game. All Rights Reserved.

#include "Weapon/STUProjectile.h"

#include "Components/SphereComponent.h"

ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	SetRootComponent(CollisionComponent);
}
