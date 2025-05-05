// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TracioAnimInstance.generated.h"

class AEnemyTracio;
class UCharacterMovementComponent;

UCLASS()
class GLADIATORGAME_API UTracioAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	//Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Values)
	bool bShouldMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Values)
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Values)
	AEnemyTracio* OwnerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Values)
	UCharacterMovementComponent* OwnerMovementComponent;
	
	//Functions
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;
	
};
