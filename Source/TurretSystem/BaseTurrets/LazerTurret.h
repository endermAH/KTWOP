// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretSystem\BaseActors\BaseTurret.h"
#include "TurretSystem\BaseActors\LazerBullet.h"
#include "LazerTurret.generated.h"

UCLASS()
class TURRETSYSTEM_API ALazerTurret : public ABaseTurret
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALazerTurret();

	UPROPERTY(BlueprintReadWrite)
	TArray<UBaseStatus*> Statuses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLazerStats LazerStats;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


#pragma region ShootImplement
	
	UPROPERTY(EditInstanceOnly)
	float ShootDelay = 5;

	/** type of bullet */
	UPROPERTY(EditDefaultsOnly, Category=Damage)
	TSubclassOf<ABaseLazer> LazerType;

	float Delay = 0;

	virtual void Shoot(float DeltaTime) override;



#pragma endregion 
	
};
