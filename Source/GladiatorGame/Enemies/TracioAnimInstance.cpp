// Fill out your copyright notice in the Description page of Project Settings.


#include "TracioAnimInstance.h"

#include "EnemyTracio.h"

void UTracioAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<AEnemyTracio>(TryGetPawnOwner());
	if (!IsValid(OwnerCharacter)) return;

	OwnerMovementComponent = OwnerCharacter->GetCharacterMovement();
	
}

void UTracioAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (OwnerMovementComponent == nullptr) return;

	const FVector Speed = OwnerCharacter->GetVelocity();

	MoveSpeed = Speed.Size();
	bShouldMove = MoveSpeed > 0.f;
}
