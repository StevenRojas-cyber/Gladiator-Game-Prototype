// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GladiatorGame/Player/PlayerCharacter.h"
#include "HitDetechNotifyState.generated.h"

class APlayerCharacter;
class AEnemyTracio;

/**
 * 
 */
UCLASS()
class GLADIATORGAME_API UHitDetechNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	//Components
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation Name")
	FName CurrentAnimation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	APlayerCharacter* OwnerPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	AEnemyTracio* OwnerEnemy;
	
	//Funtions
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	void PlayerHitDetech(UAnimSequenceBase* CurrentSequence);
	void EnemyHitDetech(UAnimSequenceBase* CurrentSequence);
};
