// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyTracio.generated.h"

class UStaticMeshComponent;


UCLASS()
class GLADIATORGAME_API AEnemyTracio : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyTracio();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//Components
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equipment)
	UStaticMeshComponent* SwordMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equipment)
	UStaticMeshComponent* ShieldMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equipment)
	UStaticMeshComponent* HelmentMeshComp;

	//Functions
	void EnemyHitDetech(FName Start, FName End, float Radius, float Time);

};
