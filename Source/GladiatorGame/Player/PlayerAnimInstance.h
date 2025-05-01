// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

class APawn;
class APlayerCharacter;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class GLADIATORGAME_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	//Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Variables)
	bool bShouldMove = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Variables)
	float GroundVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Variables)
	APawn* OwnerPawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Variables)
	APlayerCharacter* OwnerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Variables)
	UCharacterMovementComponent* OwnerMovementComponent;

	

protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;
};
