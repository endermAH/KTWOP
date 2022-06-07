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
	AActor::Tick(DeltaTime);
	if (IsWorking)
	{
		Delay -= DeltaTime;
		if ((Delay < 0))
		{
			auto* Instance = Cast<UKTWOPGameInstance>(GetGameInstance());
			if (IsValid(Instance))
			{
				Instance->IncreaseSouls(ModifiedStats.TaxStats.SoulsPerTick*ModifiedStats.TaxStats.IncomeModifier);
				Instance->IncreaseStones(ModifiedStats.TaxStats.StonesPerTick*ModifiedStats.TaxStats.IncomeModifier);
			}
			BP_OnTaxCollected(ModifiedStats.TaxStats.SoulsPerTick*ModifiedStats.TaxStats.IncomeModifier,
				ModifiedStats.TaxStats.StonesPerTick*ModifiedStats.TaxStats.IncomeModifier);
			
			Delay = ModifiedStats.TaxStats.TaxTickDelay*ModifiedStats.TaxStats.TaxTickDelayModifier;
		}
	}
	
}

void ATaxTurret::GetDelay(float& Seconds, float& Percent)
{
	Seconds = FMath::Max(0.f, Delay);
	Percent = Seconds / (ModifiedStats.TaxStats.TaxTickDelay*ModifiedStats.TaxStats.TaxTickDelayModifier);
}

void ATaxTurret::RealShoot_Implementation(float DeltaTime)
{auto* Instance = Cast<UKTWOPGameInstance>(GetGameInstance());
	if (IsValid(Instance))
	{
		Instance->IncreaseSouls(ModifiedStats.TaxStats.SoulsPerTick*ModifiedStats.TaxStats.IncomeModifier);
		Instance->IncreaseSouls(ModifiedStats.TaxStats.SoulsPerTick*ModifiedStats.TaxStats.IncomeModifier);
	}
}

void ATaxTurret::TurnOn()
{
	Super::TurnOn();
	Delay = ModifiedStats.TaxStats.TaxTickDelay*ModifiedStats.TaxStats.TaxTickDelayModifier;
	check(Delay!=0);
	CollisionComponent->Deactivate();
}

