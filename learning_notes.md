# 2. Bases

## lesson 7.
Saved\Logs
Saved\Crashed

## lesson 8. Logs
GEngine->AddOnScreenDebugMessage
*DEFINE_LOG_CATEGORY_STATIC* - LogCategory only in source file

*FName* - lightweight system for using strings. **Case-insensitive**, immutable and cannot be manipulated.
INVALID_NAME_CHARACTERS, IsValidObjectName.
FName(TEXT("SomeName"), *FNAME_Find*) -> NAME_None

*FText* - primary component for text localization
AsCultureInvariant - for non-localized text

[FText ->] FString -> FName conversion is lossy 
FText -> FString conversion is lossy for some languages

## lesson 9. UENUM
UENUM(Meta = (Bitflags))
ENUM_CLASS_FLAGS(EColorBits) -> UPARAM/UPROPERTY (meta = (Bitmask, BitmaskEnum = "EColorBits"))

## lesson 10. Components
UActorComponent - abstract behaviors
USceneComponent - location-based behaviors that do not require a geometric representation
UPrimitiveComponent - geometric representation. render/collide/overlap

CreateDefaultSuboject
SetRootComponent
SetupAttachment - useful in constructors and when dealing with Components that haven't been registered yet
AttachToComponent - useful during play
RegisterComponent/UnregisterComponent - during play
bCanEverTick/SetTickFunctionEnable

## lesson 14. Spawn
UWorld::SpawnActor
UWorld::SpawnActorDeferred + AActor::FinishSpawning

## lesson 15. Delegates
DECLARE_[MULTICAST]/[DYNAMIC]DELEGATE
use IsBound to prevent one object multi bind or single multicast rebind

## lesson 16. Gameplay Framework
GameInstance -> Levels
Level -> GameMode -> GameState -> PlayerState Array
GameMode -> AController (Player/AI) -> PlayerState/Pawn
PlayerController -> HUD/Input/CameraManager
AIController -> BehaviourTree

## lesson 18.
UGameplayStatics::GetAllActorsOfClass

## lesson 19. Modules, Targets
Modules are the building blocks of UE.

UBT supports building several target types:
Game: A standalone game which requires cooked data to run.
Client: Same as Game, but does not include any server code. Useful for networked games.
Server: Same as Game, but does not include any client code. Useful for dedicated servers in networked games.
Editor: A target which extends the Unreal Editor.
Program: A standalone utility program built on top of the Unreal Engine.

## lesson 20. Garbage Collector
for property field use TObjectPtr. Sseful for automatic replacement of raw pointers to support advanced cook-time dependency tracking and editor-time lazy load use case (wtf?)
for non-property field use TWeakObjectPtr

<br><br>

# 3. Project, Animations

## lesson 22. 
Project Description - Legal - copyrights
RMB - Asset Actions - Migrate

## lesson 25. Input and movement
SetupPlayerInputComponent -> BindAction, BindAxis
AddMovementInput -> GetActorForwardVector/GetActorRightVector/GetActorUpVector

## lesson 26. Input and camera
AddControllerPitchInput/AddControllerYawInput
UCameraComponent::bUsePawnControlRotation, Input Pitch Scale
USpringArmComponent::bUsePawnControlRotation

## lesson 27. Anim Blueprint
Skeletal Mesh Actions -> Create -> Anim Blueprint / Animation -> Animation Blueprint
Animation -> Blend Space -> Velocity from UCharacterMovementComponent

## lesson 28. Jump, Animation State Machine
ACharacter::Jump
UCharacterMovementComponent::IsFalling
Character Movement Component Jump Z Velocity
AnimGraph -> Animation State Machine

## lesson 28. Run
Transition -> Transition Rule -> Promote to Shared
UCharacterMovementComponent::GetMaxSpeed

## lesson 30.
**Left coordinate system**
Event Graph -> Is Valid
Draw Debug Arrow
FMath::Sign

<br><br>

# 4. Character Health

## lesson 33.
UTextRenderComponent
meta = (ClampMin, ClampMax)
**Assertions**
check[f][Slow]
checkCode/checkNoEntry/checkNoReentry/checkNoRecursion/unimplemented
USE_CHECKS_IN_SHIPPING - enable all except *Slow*. defaul 0

verify[f][Slow] - only when the expression needs to run independently of diagnostic checks.
In shipping builds, will ignore the return value, but will still perform the action.

ensure[Msgf]/ensureAlways[Msgf]/ - works with non-fatal errors. will inform the crash reporter, but will continue running.

## lesson 34-36. Damage
APawn::TakeDamage
AActor::OnTakeAnyDamage

ApplyRadialDamage -> ECollisionChannel DamagePreventionChannel. damage block by collision
Config/DefaultEngine.ini -> [Core.Log] LogDamage=VeryVerbose

UGameplayStatics::ApplyDamage
UDamageType

## lesson 37. Animation Montage. Death
Animation Sequence -> Animation Montage
ACharacter::PlayAnimMontage
State Machine -> Slot -> Enable Auto Blend Out (disable blend after slot animation end)

UCharacterMovementComponent::DisableMovement
AActor::SetLifeSpan

## lesson 38. ASpectatorPawn
AController::ChangeState(NAME_Spectating)

## lesson 39.
meta = (EditCondition = "[!]bool_field")
FMath::Clamp

## lesson 40. Landed
ACharacter::LandedDelegate
FMath::GetMappedRangeValueClamped

<br><br>

# 5. Weapon

## lesson 44.
UPrimitiveComponent::SetOwnerNoSee

## lesson 46. Collisions
Console - *Stat GPU/Show Collision*
*Block* - both block. *Simulation Generates Hit Events* work work individually. (be careful with spam reports)
*Overlap* - both overlap / overlap + block. *Generate Overlap Events* work only when both enable.
*Ignore* - at least one ignore.

## lesson 50. Aim Offset
Get Base Aim Rotation
Anim Sequence Details -> Additive Settings -> Mesh Space
Add Aim Offset to AnimGraph

## lesson 51. FABRIK (Forward And Backward Reaching Inverse Kinematics)
Solver (Tip Bone, Root Bone) -> End Effector (Effector Target )
The Tip will try to reach the End Effector location. Bones to use - from the Root to the Tip

## lesson 52.
FMath::VRandCone
FMath::DegreesToRadians <->

## lesson 55. Projectile Movement
UProjectileMovementComponent
MC->Velocity = Direction (Normal Vector) * MC->Initial Speed
Projectile Gravity Scale

## lesson 56. Projectile Collision
UPrimitiveComponent::IgnoreActorWhenMoving
UPrimitiveComponent::OnComponentHit

## lesson 58. Animation Notify
UAnimSequenceBase::Notifies
UAnimNotify

## lesson 60. Cached Poses
Equip animation slot changed to upper body and used locomotion cache (prevent default slot use)
Layered blend per bone - Cached locomotion + upper body result.

<br><br>

# 6. UMG (Unreal Motion Graphics)

## lesson 68. UUserWidget
UUserWidget::AddToViewport
UUserWidget::RemoveFromParent

## lesson 68. Weapon Crosshair
UTexture2D

<br><br>

# 7. Pickups

## lesson 78. Actor Rotation
AActor::AddActorLocal[Offset][Transform][Rotation]
FMath::RandBool

<br><br>

# 8. VFX, Niagara

## lesson 81. Niagara
Particle System (Cascade) - old legacy
Niagara Emitter -> Niagara System

## lesson 82. UWeaponFXComponent
UNiagaraComponent
UNiagaraSystem
UNiagaraFunctionLibrary::SpawnSystemAtLocation

## lesson 83. Physical Materials
UPhysicalMaterial
FHitResult::PhysMaterial
FCollisionQueryParams::bReturnPhysicalMaterial
UPrimitiveComponent::bReturnMaterialOnMove

## lesson 84. Decal
ADecalActor
UDecalComponent

UGameplayStatics::SpawnDecalAtLocation
Decal Lifetime Opacity
UDecalComponent::SetFadeOut

## lesson 85. Ragdoll
ECollisionEnabled::QueryAndPhysics
SetSimulatePhysics(true)

## lesson 86. Camera Shake
ULegacyCameraShake
APlayerCameraManager::StartCameraShake (APlayerController contains)

## lesson 87.
BlueprintImplementableEvent

## lesson 88. Camera Post Process
UCameraComponent::FPostProcessSettings

## lesson 89. Muzzle Effect
UNiagaraFunctionLibrary::SpawnSystemAttached
EAttachLocation::SnapToTarget
UNiagaraComponent::SetPaused
UNiagaraComponent::SetVisibility

## lesson 90. NE Beam
Beam Emitter Setup - Absolute Emitter End
Parameters -> User Exposed -> Vector -> Beam End Link Input
UNiagaraComponent::SetVariableVec3
UNiagaraComponent::Deactivate
Inactive Response -> Complete (Finish then Kill)

<br><br>

# 9. AI

## lesson 93. Navigation Mesh Volume
AAIController -> AI MoveTo + Nav Mesh Bounds Volume

## lesson 94. Blackboard + Behaviour Tree
AAIController::RunBehaviorTree
AAIController::GetBlackboardComponent
Apostrophe - AI debug
**Composite Nodes - root of a branch and the base rules for how is executed**
*Selector* - first succeed -> success
*Sequence* - first fail -> fail
*Simple Parallel* - allows a single main Task node to be executed alongside of a full tree
**Tasks - leaves of the Tree**
*Finish With Result*
*Make Noise*
*Move Directly Toward* - without regard to any navigation system
*Move To*
*Play Animation/Sound*
*Push Pawn Action*
*Rotate to face BB entry* - must have *Use Controller Rotation Yaw*
*Run Behavior* - cannot be modified at runtime
*Run Behavior Dynamic* - not support a subtree's Root-level Decorator
*Run EQS Query* - runs the specified Environment Query System
*Set Tag Cooldown*
*Wait*
*Wait Blackboard Time*

## lesson 94. Custom BT Task. 
FBlackboardKeySelector
UBTTaskNode::ExecuteTask
UNavigationSystemV1::GetCurrent
UNavigationSystemV1::GetRandomReachablePointInRadius
UBlackboardComponent::SetValueAsVector

UCharacterMovementComponent::bUseControllerDesiredRotation - smoothly rotate (clear bUseControllerRotationYaw)
UCharacterMovementComponent::RotationRate

## lesson 97. Perception Component
UAIPerceptionComponent
AAIController::SetPerceptionComponent
UAIPerceptionComponent::GetCurrentlyPerceivedActors

## lesson 98. Perception Component
**Decorator Nodes - known as conditionals**
*Blackboard* - will check to see if a value is set
*Check Gameplay Tag Condition*
*Compare BBEntries* - compare the values of two Blackboard Keys
*Composite* - AND nodes, OR nodes, and NOT nodes
*Conditional Loop* - execution loop
*Cone Check*
*Cooldown*
*Does Path Exist*
*Force Success*
*Is At Location*
*Is BBEntry Of Class* - designated Blackboard Key is of a specified Class
*Keep in Cone*
*Loop* - loops a number of times, or infinitely
*Set Tag Cooldown*
*Tag Cooldown*
*Time Limit* - give amount of time to finish before stop and fail

UBTService
UBTService::TickNode
**Service Nodes - attach to Composite nodes, execute at their frequency**
*Default Focus* - set the focus of the AI Controller to Key (can use GetFocusActor)
*Run EQS* - execute EQS template and can update a specified Key

## lesson 102. Behaviour tree stop
UBrainComponent::Cleanup

## lesson 103. Environment Query System
AEQSTestingPawn
**Generator - produces the locations or Actors, referred to as Items**
*Actors of Class* - finds all of the Actors of a given class
*Composite* - can add multiple Generators to an array
*Current Location* - get the location of the specified Context
*Points: Circle/Cone/Donut/Grid/Pathing Grid*

**Contexts - provides a frame of reference for the various Tests and Generators**
*EnvQueryContext_Item* - a location or an Actor from generator
*EnvQueryContext_Querier* - the Pawn that is currently executing

**Tests - establishes which Item from the Generator is the best option**
Filter/Score/Filter and Score

*Distance* - return the direct distance
*Dot* - calculates the Dot Product of two vectors
*Gameplay Tags* - specify a Tag to query and attempt to match in your Test
*Overlap* - determine if an Item(s) are within the bounds
*Pathfinding [Batch]* - determine if a path exists to (or from) the Context, how expensive or how long
*Project* - used to project the resulting Items onto the NavMesh
*Trace* - will trace to (or from)

## lesson 104. Custom Context
UEnvQueryContext::ProvideContext
UEnvQueryItemType_Actor::SetContextHelper

## lesson 107. Custom Test
UEnvQueryTest::RunTest
UEnvQueryTest::Cost
UEnvQueryTest::ValidItemType
UEnvQueryTest::SetWorkOnFloatValues

<br><br>

# 10. Game Mode

## lesson 111. Spawn AI
FActorSpawnParameters
FActorSpawnParameters::SpawnCollisionHandlingOverride
AGameModeBase::RestartPlayer

*BlueprintNativeEvent* - autogenerated code will call the _Implementation method if no Blueprint override is found
AGameModeBase::GetDefaultPawnClassForController -> BlueprintNativeEvent -> GetDefaultPawnClassForController_Implementation

## lesson 113. Restart
APawn::Reset - destroy pawn
AGameModeBase::RestartPlayer - create new pawn
EAutoPossessAI::Disabled
bWantsPlayerState = true;

## lesson 114. APlayerState
UWorld::GetControllerIterator
TActorIterator<T> It(World)

## lesson 117. Round Info
Time Seconds To String

## lesson 120. Game Over
TActorRange<T>(GetWorld())
APawn::TurnOff
APawn::DisableInput

## lesson 121. OnNewPawn
AController::GetOnNewPawnNotifier - not work when game mode use RestartPlayer (because call AController::SetPawn before AController::Possess)

## lesson 123. Camera Dead Zones
UPrimitiveComponent::SetOwnerNoSee
USceneComponent::GetChildrenComponents
USceneComponent::GetAttachChildren

<br><br>

# 11. Game Interfaces

## lesson 127. Game Pause
AGameModeBase::SetPause
AGameModeBase::ClearPause
meta = (BindWidget) - dynamic widget bind to class field with same type and name

APlayerController::bShowMouseCursor
SetInputMode(FInputModeGameOnly/FInputModeUIOnly/FInputModeGameAndUI)

## lesson 128. Game Over Widget
CreateWidget
UPanelWidget::AddChild
UPanelWidget::ClearChildren
APlayerState::GetPlayerName

## lesson 129. Reset Level
UUserWidget::NativeOnInitialized
UGameplayStatics::GetCurrentLevelName
UGameplayStatics::OpenLevel
AGameModeBase::ResetLevel - better alternative, but need define Reset for everything

## lesson 134. Game Quit
UKismetSystemLibrary::QuitGame

## lesson 135.
meta = (Tooltip)
UImage::SetBrushFromTexture

## lesson 136. UWidgetComponent
UWidgetComponent::SetWidgetSpace(World/Screen)
UWidgetComponent::SetDrawAtDesiredSize
UWorld::GetFirstPlayerController
APlayerController::GetPawnOrSpectator
FVector::Distance

## lesson 137.
Widget Switcher

## lesson 138. Interface animations
meta = (BindWidgetAnim) + *Transient*
UWidgetAnimation
UUserWidget::IsAnimationPlaying
UUserWidget::PlayAnimation
UUserWidget::OnAnimationFinished_Implementation

<br><br>

# 12. Sound

## lesson 144. Play Sound Animation Notify

## lesson 146. USoundClass 
Sound -> Sound Cue -> Sound Class 

## lesson 147. Sound Attenuation
Console - *Audio3DVisualize*

Attenuation Distance
Attenuation Spatialization
Attenuation Air Absorption
Attenuation Listener Focus
Attenuation Reverb Send
Attenuation Occlusion

## lesson 148. 
*UGameplayStatics::PlaySound2D* play sound without Attenuation
*UGameplayStatics::PlaySoundAtLocation/Attached* play sound with Attenuation
*UGameplayStatics::SpawnSoundAtLocation/Attached* return AudioComponent for use (Play(),SetPaused(),Stop())

## lesson 150.
EG *Flip Flop* - alternates between A/B
USoundClass Childs

## lesson 152. Sound Mix

<br><br>

# 13. Bonuses
## lesson 154. Weapon Zoom
UInputComponent::BindAction<DelegateType> can use delegate with payload
PlayerCameraManager->SetFOV
PlayerCameraManager->DefaultFOV

## lesson 155. Headshot
USkeletalMeshComponent::GetBodyInstance by bone name
FBodyInstance::GetSimplePhysicalMaterial get phys.mat from mesh

## lesson 156. AI Sense Damage
PerceptionComponent property already in AAIController. Move custom class to private.
TArray::RemoveAllSwap cheaper remove without shuffling

UAISense_Damage::ReportDamageEvent
UAISense_Hearing::ReportNoiseEvent etc.

## lesson 157. Maps from UE4
Need rebuild level nav, light, reflections after import from ue4. Thats help with some strange nullptr components asserts.
