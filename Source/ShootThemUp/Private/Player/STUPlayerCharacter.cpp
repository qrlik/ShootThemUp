// Shoot Them Up Game. All Rights Reserved.

#include "Player/STUPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/STUWeaponComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASTUPlayerCharacter::ASTUPlayerCharacter(const FObjectInitializer& Initializer):
	Super(Initializer) {
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
	CameraCollisionComponent->SetupAttachment(CameraComponent);
	CameraCollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void ASTUPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUBaseCharacter::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUBaseCharacter::StopRun);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent.Get(), &USTUWeaponComponent::Reload);
	PlayerInputComponent->BindAction("NextWeapon", IE_Released, WeaponComponent.Get(), &USTUWeaponComponent::NextWeapon);

	DECLARE_DELEGATE_OneParam(FZoomInputSignature, bool);
	PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Pressed, WeaponComponent.Get(), &USTUWeaponComponent::Zoom, true);
	PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Released, WeaponComponent.Get(), &USTUWeaponComponent::Zoom, false);

	PlayerInputComponent->BindAxis("Fire", WeaponComponent.Get(), &USTUWeaponComponent::OnFire);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::AddControllerYawInput);
}

void ASTUPlayerCharacter::BeginPlay() {
	Super::BeginPlay();

	check(SpringArmComponent);
	check(CameraComponent);
	check(CameraCollisionComponent);

	CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASTUPlayerCharacter::OnCameraBeginOverlap);
	CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ASTUPlayerCharacter::OnCameraEndOverlap);
}

void ASTUPlayerCharacter::OnDeathImpl() {
	WeaponComponent->Zoom(false);
	if (Controller) {
		Controller->ChangeState(NAME_Spectating);
	}
}

void ASTUPlayerCharacter::OnHealthChangedImpl(float Delta) const {
	if (Delta < 0.f) {
		PlayCameraShake();
	}
}

void ASTUPlayerCharacter::MoveForward(float Amount) {
	if (!FMath::IsNearlyZero(Amount)) {
		AddMovementInput(GetActorForwardVector(), Amount);
	}
	UpdateMovementFlag(EMovementFlags::MoveForward, (Amount > 0.f) ? Amount : 0.f);
}

void ASTUPlayerCharacter::MoveRight(float Amount) {
	if (!FMath::IsNearlyZero(Amount)) {
		AddMovementInput(GetActorRightVector(), Amount);
	}
	UpdateMovementFlag(EMovementFlags::MoveSide, Amount);
}

void ASTUPlayerCharacter::OnCameraBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                               int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (Cast<UPrimitiveComponent>(GetCapsuleComponent()) == OtherComp) {
		UpdateMeshRenderState(false);
	}
}

void ASTUPlayerCharacter::OnCameraEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                             int32 OtherBodyIndex) {
	if (Cast<UPrimitiveComponent>(GetCapsuleComponent()) == OtherComp) {
		UpdateMeshRenderState(true);
	}
}

void ASTUPlayerCharacter::UpdateMeshRenderState(bool Visible) const {
	GetMesh()->SetOwnerNoSee(!Visible);
	for (const auto Child : GetMesh()->GetAttachChildren()) {
		if (auto* Primitive = Cast<UPrimitiveComponent>(Child)) {
			Primitive->SetOwnerNoSee(!Visible);
		}
	}
}

void ASTUPlayerCharacter::PlayCameraShake() const {
	if (const auto* PController = GetController<APlayerController>(); PController && PController->PlayerCameraManager) {
		PController->PlayerCameraManager->StartCameraShake(CameraShake);
	}
}
