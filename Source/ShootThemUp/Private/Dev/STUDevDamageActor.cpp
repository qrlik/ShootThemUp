// Shoot Them Up Game. All Rights Reserved.

#include "Dev/STUDevDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ASTUDevDamageActor::ASTUDevDamageActor() {
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
}

void ASTUDevDamageActor::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, Color);
}

void ASTUDevDamageActor::BeginPlay() {
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(Timer, this, &ASTUDevDamageActor::DoDamage, Frequency, true);
}

void ASTUDevDamageActor::DoDamage() {
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, DamageType, {}, this, nullptr, DoFullDamage);
}
