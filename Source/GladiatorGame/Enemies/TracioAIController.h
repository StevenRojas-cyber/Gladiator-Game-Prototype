// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TracioAIController.generated.h"

class AActor;
class UBehaviorTree;

/**
 * 
 */
UCLASS()
class GLADIATORGAME_API ATracioAIController : public AAIController
{
	GENERATED_BODY()

public:
	//Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
	UBehaviorTree* BehaviorTreeComponet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
	AActor* Target;
	
	//Functions
	ATracioAIController();
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	
};
