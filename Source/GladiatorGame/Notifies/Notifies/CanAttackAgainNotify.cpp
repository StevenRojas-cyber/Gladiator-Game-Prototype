// Fill out your copyright notice in the Description page of Project Settings.


#include "CanAttackAgainNotify.h"

#include "GladiatorGame/Player/PlayerCharacter.h"

void UCanAttackAgainNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	APlayerCharacter* OwnerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());

	if (!IsValid(OwnerCharacter)) return;
	OwnerCharacter->bIsAttacking = false;
	
}
