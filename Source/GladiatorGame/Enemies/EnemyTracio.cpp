// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTracio.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AEnemyTracio::AEnemyTracio()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SwordMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("SwordMesh");
	SwordMeshComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "SwordSocket_2");
	//SwordMeshComp->SetCollisionProfileName()
	
	ShieldMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("ShieldMesh");
	ShieldMeshComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "ShieldSocket_2");
	
	HelmentMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("HelmetMesh");
	HelmentMeshComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "HelmentSocket_2");

	Tags.Add("Enemy");
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
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

void AEnemyTracio::EnemyHitDetech(FName Start, FName End, float Radius, float Time)
{
	FVector TraceStart;
	FVector TraceEnd;

	TraceStart = GetMesh()->GetSocketLocation(Start);
	TraceEnd = GetMesh()->GetSocketLocation(End);

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	FHitResult HitActor;

	UKismetSystemLibrary::SphereTraceSingle(GetWorld(), TraceStart, TraceEnd, Radius, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitActor, true, FLinearColor::Red, FLinearColor::Green, Time);

	if (HitActor.bBlockingHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Orange, HitActor.GetActor()->GetName());
	}
}
