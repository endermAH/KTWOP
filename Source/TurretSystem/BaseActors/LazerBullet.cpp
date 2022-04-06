// Fill out your copyright notice in the Description page of Project Settings.
#include "LazerBullet.h"

// Sets default values
ABaseLazer::ABaseLazer()
{
	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lazer"));
	
	PrimaryActorTick.bCanEverTick = true;
	
	//AbilitySystemComponent = CreateDefaultSubobject<UBulletAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	//AbilitySystemComponent->SetIsReplicated(true);
	
}

// Called when the game starts or when spawned
void ABaseLazer::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseLazer::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}


// Called every frame
void ABaseLazer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

