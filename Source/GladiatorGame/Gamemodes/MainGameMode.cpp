// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "GameFramework/HUD.h"
#include "UObject/ConstructorHelpers.h"

AMainGameMode::AMainGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> BP_PlayerCharacter(TEXT("/Game/Blueprints/Player/BP_PlayerCharacter"));
	if (!IsValid(BP_PlayerCharacter.Class)) return;

	DefaultPawnClass = BP_PlayerCharacter.Class;

	static ConstructorHelpers::FClassFinder<AHUD> BP_HUD(TEXT("/Game/Blueprints/HUD/BP_MainHUDClass"));
	if (!IsValid(BP_HUD.Class)) return;

	HUDClass = BP_HUD.Class;
}
