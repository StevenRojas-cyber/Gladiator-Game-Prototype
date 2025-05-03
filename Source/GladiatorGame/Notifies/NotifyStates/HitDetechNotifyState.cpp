// Fill out your copyright notice in the Description page of Project Settings.


#include "HitDetechNotifyState.h"

#include "GladiatorGame/Player/PlayerCharacter.h"

void UHitDetechNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	
	FName CurrentAnimation = FName(*Animation->GetName());
	
	if (CurrentAnimation == NAME_None) return;

	if (CurrentAnimation == "Slash_1" || CurrentAnimation == "Slash_2")
	{
		APlayerCharacter* OwnerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
		if (!IsValid(OwnerCharacter)) return;
		
		OwnerCharacter->HitDetech("hand_r", "hand_r", 30);
	}
	else if (CurrentAnimation == "Kick")
	{
		APlayerCharacter* OwnerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
		if (!IsValid(OwnerCharacter)) return;
		
		OwnerCharacter->HitDetech("foot_r", "foot_r", 30);
	}
}
