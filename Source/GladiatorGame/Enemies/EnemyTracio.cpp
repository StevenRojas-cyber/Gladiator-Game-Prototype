// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTracio.h"

// Sets default values
AEnemyTracio::AEnemyTracio()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SwordMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("SwordMesh");
	SwordMeshComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "SwordSocket_2");
	
	ShieldMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("ShieldMesh");
	ShieldMeshComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "ShieldSocket_2");
	
	HelmentMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("HelmetMesh");
	HelmentMeshComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "HelmentSocket_2");
}

// Called when the game starts or when spawned
void AEnemyTracio::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyTracio::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyTracio::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

