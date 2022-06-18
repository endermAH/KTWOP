// Fill out your copyright notice in the Description page of Project Settings.


#include "TaxTurret.h"

#include "GameplaySystem/GameplayClasses/KTWOPGameInstance.h"


// Sets default values
ATaxTurret::ATaxTurret()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATaxTurret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATaxTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsWorking && ModifiedStats.TaxStats.CanProduce && !ModifiedStats.TaxStats.CanNotProduce)
	{
		TaxDelay -= DeltaTime;
		if ((TaxDelay < 0))
		{
			auto* Instance = Cast<UKTWOPGameInstance>(GetGameInstance());
			if (IsValid(Instance))
			{
				Instance->IncreaseSouls(ModifiedStats.TaxStats.SoulsPerTick*ModifiedStats.TaxStats.IncomeModifier);
				Instance->IncreaseStones(ModifiedStats.TaxStats.StonesPerTick*ModifiedStats.TaxStats.IncomeModifier);
			}
			BP_OnTaxCollected(ModifiedStats.TaxStats.SoulsPerTick*ModifiedStats.TaxStats.IncomeModifier,
				ModifiedStats.TaxStats.StonesPerTick*ModifiedStats.TaxStats.IncomeModifier);
			
			TaxDelay = ModifiedStats.TaxStats.TaxTickDelay*ModifiedStats.TaxStats.TaxTickDelayModifier;
		}
	}
	
}

void ATaxTurret::GetTaxDelay(float& Seconds, float& Percent)
{
	Seconds = FMath::Max(0.f, TaxDelay);
	Percent = Seconds / (ModifiedStats.TaxStats.TaxTickDelay*ModifiedStats.TaxStats.TaxTickDelayModifier);
}

void ATaxTurret::RealShoot_Implementation(float DeltaTime)
{
	auto* Instance = Cast<UKTWOPGameInstance>(GetGameInstance());
	if (IsValid(Instance))
	{
		Instance->IncreaseSouls(ModifiedStats.TaxStats.SoulsPerTick*ModifiedStats.TaxStats.IncomeModifier);
		Instance->IncreaseSouls(ModifiedStats.TaxStats.SoulsPerTick*ModifiedStats.TaxStats.IncomeModifier);
	}
}

void ATaxTurret::TurnOn()
{
	Super::TurnOn();
	TaxDelay = ModifiedStats.TaxStats.TaxTickDelay*ModifiedStats.TaxStats.TaxTickDelayModifier;
	check(TaxDelay!=0 || !ModifiedStats.TaxStats.CanProduce || ModifiedStats.TaxStats.CanNotProduce);
	//CollisionComponent->Deactivate();
}

