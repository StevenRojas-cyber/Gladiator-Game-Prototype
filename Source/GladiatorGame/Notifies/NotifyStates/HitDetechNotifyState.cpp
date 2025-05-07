// Fill out your copyright notice in the Description page of Project Settings.


#include "HitDetechNotifyState.h"
#include "GladiatorGame/Player/PlayerCharacter.h"
#include "GladiatorGame/Enemies/EnemyTracio.h"

void UHitDetechNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (!IsValid(MeshComp)) return;

	AActor* Owner = MeshComp->GetOwner();

	if (Owner && Owner->GetWorld() && !Owner->GetWorld()->IsPreviewWorld())
	{
		OwnerPlayer = Cast<APlayerCharacter>(Owner);
		OwnerEnemy  = Cast<AEnemyTracio>(Owner);
	}
}

void UHitDetechNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	
	if (IsValid(OwnerPlayer))
	{
		if (!IsValid(Animation)) return;
		PlayerHitDetech(Animation);
	}
	else if (IsValid(OwnerEnemy))
	{
		if (!IsValid(Animation)) return;
		EnemyHitDetech(Animation);
	}
}

void UHitDetechNotifyState::PlayerHitDetech(UAnimSequenceBase* CurrentSequence)
{
	CurrentAnimation = FName(*CurrentSequence->GetName());
	
	if (CurrentAnimation == NAME_None) return;

	if (CurrentAnimation == "Slash_1" || CurrentAnimation == "Slash_2")
	{	
		OwnerPlayer->HitDetech("hand_r", "hand_r", 40, 2);
	}
	else if (CurrentAnimation == "Kick")
	{
		
		OwnerPlayer->HitDetech("foot_r", "foot_r", 40, 2);
	}
}

void UHitDetechNotifyState::EnemyHitDetech(UAnimSequenceBase* CurrentSequence)
{
	CurrentAnimation = FName(*CurrentSequence->GetName());

	if (CurrentAnimation == NAME_None) return;

	if (CurrentAnimation == "Enemy_Slash1")
	{
		OwnerEnemy->EnemyHitDetech("SwordSocket_2", "SwordSocket_2", 40, 2);
	}
}


/*FName CurrentAnimation = FName(*Animation->GetName());
	
	if (CurrentAnimation == NAME_None) return;

	if (CurrentAnimation == "Slash_1" || CurrentAnimation == "Slash_2")
	{
		APlayerCharacter* OwnerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
		if (!IsValid(OwnerCharacter)) return;
		
		OwnerCharacter->HitDetech("hand_r", "hand_r", 40);
	}
	else if (CurrentAnimation == "Kick")
	{
		APlayerCharacter* OwnerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
		if (!IsValid(OwnerCharacter)) return;
		
		OwnerCharacter->HitDetech("foot_r", "foot_r", 40);
	}*/
