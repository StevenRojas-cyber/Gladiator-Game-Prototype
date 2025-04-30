// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "UObject/ConstructorHelpers.h"

AMainGameMode::AMainGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> BP_PlayerCharacter(TEXT("/Game/Blueprints/Player/BP_PlayerCharacter"));
	if (!IsValid(BP_PlayerCharacter.Class)) return;

	DefaultPawnClass = BP_PlayerCharacter.Class;
}
