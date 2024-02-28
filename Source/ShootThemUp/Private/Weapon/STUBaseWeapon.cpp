// Shoot Them Up Game. All Rights Reserved.

#include "Weapon/STUBaseWeapon.h"

#include "Components/STUWeaponFXComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All)

ASTUBaseWeapon::ASTUBaseWeapon() {
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

	FXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("VFXComponent");
}

void ASTUBaseWeapon::Destroyed() {
	StopFire();
	Super::Destroyed();
}

USTUWeaponFXComponent* ASTUBaseWeapon::GetVfx() const {
	return FXComponent;
}

bool ASTUBaseWeapon::CanReload() const {
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && (CurrentAmmo.Clips > 0 || CurrentAmmo.Infinite);
}

bool ASTUBaseWeapon::TryToAddAmmo(int32 ClipsAmount) {
	if (IsAmmoFull() || ClipsAmount <= 0) {
		return false;
	}
	if (IsAmmoEmpty()) {
		CurrentAmmo.Clips = FMath::Clamp(ClipsAmount, 0, DefaultAmmo.Clips + 1);
		OnClipEmpty.Execute();
	}
	else {
		CurrentAmmo.Clips = FMath::Clamp(CurrentAmmo.Clips + ClipsAmount, CurrentAmmo.Clips, DefaultAmmo.Clips);
	}
	return true;
}

void ASTUBaseWeapon::StartFire() {
	bShotAccepted = true;
	if (!FireTimer.IsValid()) {
		GetWorldTimerManager().SetTimer(FireTimer, this, &ASTUBaseWeapon::TryToShot, Cooldown, true, 0.f);
	}
}

void ASTUBaseWeapon::StopFire() {
	bShotAccepted = false;
}

void ASTUBaseWeapon::BeginPlay() {
	Super::BeginPlay();

	check(WeaponMesh);
	check(FXComponent);

	CurrentAmmo = DefaultAmmo;
}

FTransform ASTUBaseWeapon::GetMuzzleTransform() const {
	if (WeaponMesh) {
		return WeaponMesh->GetSocketTransform(MuzzleSocketName);
	}
	return FTransform{};
}

AController* ASTUBaseWeapon::GetController() const {
	if (const auto* Character = Cast<ACharacter>(GetOwner())) {
		return Character->GetController();
	}
	return nullptr;
}

FHitResult ASTUBaseWeapon::GetHitResult() const {
	FHitResult HitResult;
	FVector TraceStart, TraceEnd;
	GetShotTrace(TraceStart, TraceEnd);

	if (const auto* World = GetWorld()) {
		FCollisionQueryParams CollisionParams;
		CollisionParams.bReturnPhysicalMaterial = true;
		CollisionParams.AddIgnoredActor(GetOwner());

		World->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionParams);
	}
	return HitResult;
}

bool ASTUBaseWeapon::IsAmmoEmpty() const {
	return !CurrentAmmo.Infinite && CurrentAmmo.Clips <= 0 && IsClipEmpty();
}

bool ASTUBaseWeapon::IsAmmoFull() const {
	return CurrentAmmo.Infinite || CurrentAmmo.Clips >= DefaultAmmo.Clips;
}

bool ASTUBaseWeapon::IsClipEmpty() const {
	return CurrentAmmo.Bullets <= 0;
}

bool ASTUBaseWeapon::CheckEmptyClip() const {
	if (IsClipEmpty()) {
		OnClipEmpty.Execute();
		return true;
	}
	return false;
}

void ASTUBaseWeapon::MakeShot() {
	if (CheckEmptyClip()) {
		UGameplayStatics::PlaySoundAtLocation(this, NoAmmoSound, GetActorLocation());
		return;
	}
	MakeShotImpl();
	DecreaseAmmo();
	UGameplayStatics::PlaySoundAtLocation(this, ShotSound, GetActorLocation());
	FXComponent->ShowMuzzleEffect(WeaponMesh, MuzzleSocketName);
}

void ASTUBaseWeapon::MakeShotImpl() {
}

void ASTUBaseWeapon::DecreaseAmmo() {
	if (CurrentAmmo.Bullets <= 0) {
		UE_LOG(LogBaseWeapon, Warning, TEXT("ASTUBaseWeapon::DecreaseAmmo No more bullets"));
		return;
	}

	CurrentAmmo.Bullets -= 1;
	CheckEmptyClip();
}

void ASTUBaseWeapon::ChangeClip() {
	if (!CurrentAmmo.Infinite) {
		if (CurrentAmmo.Clips <= 0) {
			UE_LOG(LogBaseWeapon, Warning, TEXT("ASTUBaseWeapon::ChangeClip No more clips"));
			return;
		}

		CurrentAmmo.Clips -= 1;
	}
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	//UE_LOG(LogBaseWeapon, Display, TEXT("========= CHANGE CLIP =========="));
}

void ASTUBaseWeapon::OnEquip() const {
	CheckEmptyClip();
}

void ASTUBaseWeapon::GetShotTrace(FVector& Start, FVector& End) const {
	const auto* Controller = GetController();
	if (!Controller) {
		return;
	}
	if (Controller->IsPlayerController()) {
		FRotator ViewRotation;
		Controller->GetPlayerViewPoint(Start, ViewRotation);

		const auto HalfRad = FMath::DegreesToRadians(ShotSpread);
		const auto TraceRotation = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
		End = Start + TraceRotation * ShotDistance;
	}
	else {
		const auto Muzzle = GetMuzzleTransform();
		Start = Muzzle.GetLocation();
		End = Start + Muzzle.GetRotation().Vector() * ShotDistance;
	}
}

void ASTUBaseWeapon::TryToShot() {
	if (!bShotAccepted) {
		GetWorldTimerManager().ClearTimer(FireTimer);
		return;
	}
	MakeShot();
}

