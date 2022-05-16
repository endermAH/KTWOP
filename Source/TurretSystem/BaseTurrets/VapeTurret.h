// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework\Actor.h"
#include "TurretSystem\BaseActors\BaseTurret.h"
#include "TurretSystem\BaseActors\VapeBullet.h"
#include "VapeTurret.generated.h"

UCLASS(Abstract, Blueprintable)
class TURRETSYSTEM_API AVapeTurret : public ABaseTurret {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AVapeTurret();

	FVapeBulletStats ExplosionStats;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


#pragma region ShootImplement
	

	/** type of bullet */
	UPROPERTY(EditDefaultsOnly, Category=Damage)
	TSubclassOf<AVapeBullet> VapeType;

	float Delay = 0;

	virtual void RealShoot_Implementation(float DeltaTime) override;



#pragma endregion 
	

};
