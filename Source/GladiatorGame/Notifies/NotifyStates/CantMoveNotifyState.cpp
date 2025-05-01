// Fill out your copyright notice in the Description page of Project Settings.


#include "CantMoveNotifyState.h"

#include "GladiatorGame/Player/PlayerCharacter.h"

void UCantMoveNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	APlayerCharacter* OwnerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (!IsValid(OwnerCharacter)) return;

	OwnerCharacter->bCanMove = false;
}

void UCantMoveNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	APlayerCharacter* OwnerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (!IsValid(OwnerCharacter)) return;

	OwnerCharacter->bCanMove = true;
}
