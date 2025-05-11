// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "PlayerInterfaceWidget.generated.h"

class UTextBlock;
class UCanvasPanel;

/**
 * 
 */
UCLASS()
class GLADIATORGAME_API UPlayerInterfaceWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//COMPONENTS
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI, meta = (BindWidget))
	UCanvasPanel* MainCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI, meta = (BindWidget))
	UTextBlock* HP;

	//FUNCTIONS
	virtual void NativeConstruct() override;
	
};
