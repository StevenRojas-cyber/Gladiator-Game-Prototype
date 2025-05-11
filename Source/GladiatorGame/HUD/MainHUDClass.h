// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUDClass.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class GLADIATORGAME_API AMainHUDClass : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<UUserWidget> PlayerWidget;

	//FUNCTIONS
	virtual void BeginPlay() override;
};
