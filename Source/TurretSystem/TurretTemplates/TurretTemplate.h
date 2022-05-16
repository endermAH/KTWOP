// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject\Object.h"
#include "TurretSystem\BaseTurrets\LazerTurret.h"
#include "TurretSystem\BaseTurrets\SingleTargetTurret.h"
#include "TurretSystem\BaseTurrets\VapeTurret.h"
#include "TurretTemplate.generated.h"


/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class TURRETSYSTEM_API UTurretTemplate : public UDataAsset {
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UModuleSystem> ModuleSystemComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FModuleSystemStats ModuleSystemStats;

	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stats")
	FBaseTurretStats TurretStats;

	UFUNCTION(BlueprintCallable)
	virtual ABaseTurret* SpawnTurret(AActor* Spawner, const FTransform& Transform, const TArray<FModuleDescription>& Modules);
	
};

UCLASS(BlueprintType)
class TURRETSYSTEM_API USingleTargetTurretTemplate : public UTurretTemplate {
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Blueprints")
	TSubclassOf<ASingleTargetTurret> TurretBP;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Blueprints")
	TSubclassOf<ABaseBullet> BulletBP;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stats")
	FBulletStats BulletStats;
	
	virtual ABaseTurret* SpawnTurret(AActor* Spawner, const FTransform& Transform, const TArray<FModuleDescription>& Modules) override;
	
};


UCLASS(BlueprintType)
class TURRETSYSTEM_API ULazerTurretTemplate : public UTurretTemplate {
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Blueprints")
	TSubclassOf<ALazerTurret> TurretBP;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Blueprints")
	TSubclassOf<ABaseLazer> LazerBP;

	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stats")
	FLazerStats LazerStats;
	
	virtual ABaseTurret* SpawnTurret(AActor* Spawner, const FTransform& Transform, const TArray<FModuleDescription>& Modules) override;
	
};

UCLASS(BlueprintType)
class TURRETSYSTEM_API UVapeTurretTemplate : public UTurretTemplate {
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Blueprints")
	TSubclassOf<AVapeTurret> TurretBP;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Blueprints")
	TSubclassOf<AVapeBullet> VapeBP;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stats")
	FVapeBulletStats VapeStats;
	
	
	virtual ABaseTurret* SpawnTurret(AActor* Spawner, const FTransform& Transform, const TArray<FModuleDescription>& Modules) override;
	
};
