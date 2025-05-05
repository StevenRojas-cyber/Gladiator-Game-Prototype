// Fill out your copyright notice in the Description page of Project Settings.


#include "TracioAIController.h"
#include "EnemyTracio.h"
#include "BehaviorTree/BlackboardComponent.h"


ATracioAIController::ATracioAIController()
{
}

void ATracioAIController::BeginPlay()
{
	Super::BeginPlay();

	Target = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!IsValid(Target)) return;

	GetBlackboardComponent()->SetValueAsObject("Player", Target);
	
}

void ATracioAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AEnemyTracio* OwnerPawn = CastChecked<AEnemyTracio>(InPawn);
	if (!IsValid(OwnerPawn)) return;
	
	RunBehaviorTree(BehaviorTreeComponet);
}
