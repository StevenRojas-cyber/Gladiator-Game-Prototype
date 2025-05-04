// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TracioAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORGAME_API UTracioAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	//Functions
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;
	
};
