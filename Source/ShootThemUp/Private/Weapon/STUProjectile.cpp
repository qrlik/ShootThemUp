// Shoot Them Up Game. All Rights Reserved.

#include "Weapon/STUProjectile.h"

#include "Components/SphereComponent.h"
#include "Components/STUWeaponVFXComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/STUBaseCharacter.h"
#include "Weapon/STUBaseWeapon.h"

ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	SetRootComponent(CollisionComponent);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionComponent->bReturnMaterialOnMove = true;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
}

void ASTUProjectile::SetWeaponOwner(AActor* Character) {
	WeaponOwner = Character;
}

void ASTUProjectile::BeginPlay() {
	Super::BeginPlay();

	check(CollisionComponent);
	check(MovementComponent);

	MovementComponent->Velocity = Direction * MovementComponent->InitialSpeed;
	CollisionComponent->IgnoreActorWhenMoving(WeaponOwner, true);
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
	//DrawDebugSphere(World, GetActorLocation(), DamageRadius, 24, FColor::Red, false, LifeTime);
	PlayHitEffect(Hit);

	Destroy();
}

void ASTUProjectile::PlayHitEffect(const FHitResult& Hit) const {
	if (const auto* Weapon = Cast<ASTUBaseWeapon>(GetOwner())) {
		if (const auto* Vfx = Weapon->GetVfx()) {
			Vfx->PlayHitEffect(Hit);
		}
	}
}

AController* ASTUProjectile::GetController() const {
	const auto* Pawn = Cast<APawn>(WeaponOwner);
	return Pawn ? Pawn->GetController() : nullptr;
}
