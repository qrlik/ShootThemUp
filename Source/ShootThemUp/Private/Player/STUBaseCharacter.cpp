// Shoot Them Up Game. All Rights Reserved.

#include "Player/STUBaseCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All)

ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& Initializer):
	Super(Initializer.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(CharacterMovementComponentName)) {
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");
	WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");
}

void ASTUBaseCharacter::BeginPlay() {
	Super::BeginPlay();

	check(HealthComponent);
	check(WeaponComponent);

	OnTakeAnyDamage.AddDynamic(HealthComponent.Get(), &USTUHealthComponent::OnTakeAnyDamage);
	LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnGroundLanded);
	HealthComponent->OnHealthChange.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);
	HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
}

void ASTUBaseCharacter::OnDeathImpl() {
}

void ASTUBaseCharacter::OnHealthChangedImpl(float Delta) const {
}

float ASTUBaseCharacter::GetDirectionAngle() const {
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	if (VelocityNormal.IsZero()) {
		return 0.f;
	}
	const auto Forward = GetActorForwardVector();
	const auto Angle = FMath::Acos(Forward.Dot(VelocityNormal));
	const auto Degrees = FMath::RadiansToDegrees(Angle);
	const auto Cross = Forward.Cross(VelocityNormal);
	return (FMath::IsNearlyZero(Cross.Z)) ? Degrees : Degrees * FMath::Sign(Cross.Z);
}

USTUHealthComponent* ASTUBaseCharacter::GetHealthComponent() const {
	return HealthComponent;
}

USTUWeaponComponent* ASTUBaseCharacter::GetWeaponComponent() const {
	return WeaponComponent;
}

void ASTUBaseCharacter::SetPlayerColor(FLinearColor Color) const {
	auto* Material = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if (!Material) {
		return;
	}
	Material->SetVectorParameterValue(TeamColorMaterial, Color);
}

void ASTUBaseCharacter::OnDeath() {
	//PlayAnimMontage(DeathAnimMontage);

	if (auto* MovementComponent = GetCharacterMovement()) {
		MovementComponent->DisableMovement();
	}
	if (auto* Capsule = GetCapsuleComponent()) {
		Capsule->SetCollisionResponseToAllChannels(ECR_Ignore);
	}
	SetLifeSpan(LifeSpanOnDeath);

	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	GetMesh()->SetSimulatePhysics(true);

	OnDeathImpl(); // at the end
}

void ASTUBaseCharacter::OnHealthChanged(float Delta) const {
	OnHealthChangedImpl(Delta);
}

void ASTUBaseCharacter::OnGroundLanded(const FHitResult& Hit) {
	const auto FallVelocity = -GetVelocity().Z;
	if (FallVelocity < 0.f || FallVelocity < LandedDamageVelocity.X) {
		return;
	}
	const auto FallDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocity);
	TakeDamage(FallDamage, FDamageEvent{}, nullptr, nullptr);
}

void ASTUBaseCharacter::StartRun() {
	UpdateMovementFlag(EMovementFlags::AbleToRun, 1.f);
}

void ASTUBaseCharacter::StopRun() {
	UpdateMovementFlag(EMovementFlags::AbleToRun, 0.f);
}

void ASTUBaseCharacter::UpdateMovementFlag(EMovementFlags Flag, float Amount) const {
	if (auto* MovementComponent = FindComponentByClass<USTUCharacterMovementComponent>()) {
		if (FMath::IsNearlyEqual(Amount, 0.f)) {
			MovementComponent->RemoveMovementFlag(Flag);
		}
		else {
			MovementComponent->AddMovementFlag(Flag);
		}
	}
}
