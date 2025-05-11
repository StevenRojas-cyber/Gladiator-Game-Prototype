// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUDClass.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/PlayerInterfaceWidget.h"

void AMainHUDClass::BeginPlay()
{
	Super::BeginPlay();
	if (!IsValid(PlayerWidget)) return;
	
	UPlayerInterfaceWidget* InterfaceWidget = CreateWidget<UPlayerInterfaceWidget>(GetWorld(), PlayerWidget);
	if (!IsValid(InterfaceWidget)) return;
	
	InterfaceWidget->AddToViewport();
}
