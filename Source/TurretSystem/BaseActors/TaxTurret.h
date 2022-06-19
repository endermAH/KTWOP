// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurretSystem/BaseActors/BaseTurret.h"
#include "TaxTurret.generated.h"



UCLASS()
class TURRETSYSTEM_API ATaxTurret : public ABaseTurret
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATaxTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnTaxCollected"))
	void BP_OnTaxCollected(float Souls, float Stones);
	
	UFUNCTION(BlueprintCallable)
	void GetTaxDelay(float& Seconds, float& Percent);
	
#pragma region TaxImplement
	
	

	float TaxDelay = 1000000;

	
	virtual void RealShoot_Implementation(float DeltaTime) override;



#pragma endregion

	virtual void TurnOn() override;
};
