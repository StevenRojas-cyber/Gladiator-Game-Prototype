// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

#include "PlayerCharacter.h"

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerPawn = TryGetPawnOwner();
	if (!IsValid(OwnerPawn)) return;

	OwnerCharacter = Cast<APlayerCharacter>(OwnerPawn);
	if (!IsValid(OwnerCharacter)) return;

	OwnerMovementComponent = OwnerCharacter->GetCharacterMovement();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (OwnerMovementComponent == nullptr) return;

	const FVector velocity = OwnerCharacter->GetVelocity();

	GroundVelocity = velocity.Size();

	bShouldMove = GroundVelocity > 0.f;
}
