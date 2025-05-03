// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Class Components
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 300.0f;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;

	//Class Attributes
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;


}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance != nullptr)
	{
		AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &APlayerCharacter::MontageNotifyBegin);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (!IsValid(PlayerController)) return;

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (!IsValid(Subsystem)) return;

	Subsystem->AddMappingContext(MappingContextComponent, 0);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!IsValid(Input)) return;

	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
	Input->BindAction(AttackAction, ETriggerEvent::Started, this, &APlayerCharacter::Attack);
}


//ACTIONS//
///////////////////////////
void APlayerCharacter::Move(const FInputActionValue& InputActionValue)
{
	if (!bCanMove) return;
	FVector2d MovementVector = InputActionValue.Get<FVector2d>();
	if (!IsValid(Controller)) return;

	const FRotator CurrentRotation = Controller->GetControlRotation();
	const FRotator YawRotation = FRotator(0, CurrentRotation.Yaw, 0);

	const FVector FowardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(FowardDirection, MovementVector.Y);
	AddMovementInput(RightVector, MovementVector.X);
}

void APlayerCharacter::Look(const FInputActionValue& InputActionValue)
{
	FVector2d LookDirection = InputActionValue.Get<FVector2d>();
	if (!IsValid(Controller)) return;

	AddControllerYawInput(LookDirection.X);
	AddControllerPitchInput(LookDirection.Y);
}

void APlayerCharacter::Attack(const FInputActionValue& InputActionValue)
{

	InitAttack();
}

///////////////////////////


//DYNAMICS
///////////////////////////
void APlayerCharacter::MontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	AttackCount--;
	if (AttackCount < 0)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (!IsValid(AnimInstance)) return;
		
		AnimInstance->Montage_Stop(0.4f,ComboMontage);
	}
}

///////////////////////////

//MECHANICS
///////////////////////////
void APlayerCharacter::HitDetech(FName Start, FName End, float Radius)
{
	FVector TraceStart;
	FVector TraceEnd;

	TraceStart = GetMesh()->GetSocketLocation(Start);
	TraceEnd = GetMesh()->GetSocketLocation(End);

	TArray<AActor*> ActorsIgnore;
	ActorsIgnore.Add(this);
	FHitResult HitActor;

	UKismetSystemLibrary::SphereTraceSingle(GetWorld(), TraceStart, TraceEnd, Radius, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, ActorsIgnore, EDrawDebugTrace::ForDuration, HitActor, true, FLinearColor::Red, FLinearColor::Green, 5);

	if (HitActor.bBlockingHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, HitActor.GetActor()->GetName());
	}
}

void APlayerCharacter::InitAttack()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!IsValid(AnimInstance)) return;

	if (AnimInstance->IsAnyMontagePlaying())
	{
		AttackCount = 1;
	}
	else
	{
		AnimInstance->Montage_Play(ComboMontage, 1.5f);
	}
}

///////////////////////////