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

	Tags.Add("Player");
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerAnimInstance = GetMesh()->GetAnimInstance();
	if (PlayerAnimInstance != nullptr)
	{
		PlayerAnimInstance->OnMontageEnded.AddDynamic(this, &APlayerCharacter::OnMontageEnd);
		PlayerAnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &APlayerCharacter::MontageNotifyBegin);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(-1, 0.001f, FColor::Green, FString::Printf(TEXT("IsAttacking = %s"), bIsAttacking ? TEXT("true") : TEXT("false")));
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
	InitAttack(2.0f);
}

///////////////////////////


//DYNAMICS
///////////////////////////
void APlayerCharacter::MontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, NotifyName.ToString());
	bIsAttacking = false;
}

///////////////////////////

//MECHANICS
///////////////////////////
void APlayerCharacter::HitDetech(FName Start, FName End, float Radius, float Time)
{
	FVector TraceStart;
	FVector TraceEnd;

	TraceStart = GetMesh()->GetSocketLocation(Start);
	TraceEnd = GetMesh()->GetSocketLocation(End);

	TArray<AActor*> ActorsIgnore;
	ActorsIgnore.Add(this);
	FHitResult HitActor;

	UKismetSystemLibrary::SphereTraceSingle(GetWorld(), TraceStart, TraceEnd, Radius, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, ActorsIgnore, EDrawDebugTrace::ForDuration, HitActor, true, FLinearColor::Red, FLinearColor::Green, Time);

	
	if (HitActor.bBlockingHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, HitActor.GetActor()->GetName());
	}
}

void APlayerCharacter::OnMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	if (bInterrupted)
	{
		StartRetriggerableDelay(1.5f);
	}
	else
	{
		AttackCount = 0;
	}
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, "Fin del montage");
}


void APlayerCharacter::InitAttack(float AttackVelocity)
{
	if (!IsValid(PlayerAnimInstance)) return;
	if (bIsAttacking) return;
	bIsAttacking = true;

	switch (AttackCount)
	{
		case 0:
			PlayerAnimInstance->Montage_Play(FirstAttackMontage,AttackVelocity);
			break;

		case 1:
			PlayerAnimInstance->Montage_Play(SecondAttackMontage, AttackVelocity);
			break;

		case 2:
			PlayerAnimInstance->Montage_Play(ThirdAttackMontage, AttackVelocity);
			break;
		default:
			break;
	}

	AttackCount ++;
}


void APlayerCharacter::StartRetriggerableDelay(float Duration)
{
	if (bTimerActive)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlayerCharacter::OnDelayCompleted, Duration, false);
	bTimerActive = true;
}

void APlayerCharacter::OnDelayCompleted()
{
	bIsAttacking = false;
	AttackCount = 0;
}

