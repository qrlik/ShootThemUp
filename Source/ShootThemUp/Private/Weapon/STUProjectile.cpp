// Shoot Them Up Game. All Rights Reserved.

#include "Weapon/STUProjectile.h"

#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Components/STUWeaponVFXComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Weapon/STUBaseWeapon.h"

ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	SetRootComponent(CollisionComponent);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->bReturnMaterialOnMove = true;

	TraceComponent = CreateDefaultSubobject<UNiagaraComponent>("NiagaraComponent");
	TraceComponent->SetupAttachment(CollisionComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComponent->SetupAttachment(CollisionComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");

	AudioComponent = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
	AudioComponent->SetupAttachment(CollisionComponent);
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
	// DrawDebugSphere(World, GetActorLocation(), DamageRadius, 24, FColor::Red, false, LifeTime);
	PlayHitEffect(Hit);

	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
	AudioComponent->Stop();

	if (TraceComponent->IsActive()) {
		TraceComponent->Deactivate();
		MeshComponent->SetVisibility(false, true);
		SetLifeSpan(LifeTime);
	}
	else {
		Destroy();
	}
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
