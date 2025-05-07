// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UAnimMontage;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class GLADIATORGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	bool bCanMove = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	int32 AttackCount = 0;
	
	// Camera Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	USpringArmComponent* CameraBoom;

	//Input Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputMappingContext* MappingContextComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* AttackAction;

	//Animations
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackMontages)
	UAnimMontage* ComboMontage;

protected:
	
	//Actions Functions
	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);
	void Attack(const FInputActionValue& InputActionValue);

	//Dynamic Functions
	UFUNCTION()
	void MontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);

	//Mechanics Functions
	void InitAttack();

public:
	void HitDetech(FName Start, FName End, float Radius, float Time);
};
