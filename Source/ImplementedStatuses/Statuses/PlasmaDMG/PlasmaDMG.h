// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlasmaExplosion.h"
#include "../ExplodedStatus.h"
#include "PlasmaDMG.generated.h"

USTRUCT(BlueprintType)
struct FPlasmaStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FPlasmaExplosionStats ExplosionStats;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<APlasmaExplosion> ExplosionType;
};

/**
 * 
 */
UCLASS()
class IMPLEMENTEDSTATUSES_API UPlasmaDMG : public UExplodedStatus
{
	GENERATED_BODY()

	float CollectedDamage = 0;
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	FPlasmaStats PlasmaStats;

	void StartExplosion(const TScriptInterface<IStatusOwner>& statusOwner);
	
	float AccumulatedDuration = 0;
	
	virtual EStatusType GetStatusType_Implementation() override;
	virtual void OnTick_Implementation(const TScriptInterface<IStatusOwner>& statusOwner, float dt) override;
	virtual void Apply_Implementation(ABaseEnemy* enemy, FStatusModifier ExternalModifies) override;
	virtual void AddToBullet_Implementation(AActor* enemy, FStatusModifier ExternalModifies) override;
	virtual void OnDie_Implementation(const TScriptInterface<IStatusOwner>& statusOwner) override;
	virtual void ApplyDmg_Implementation(float damage) override;
	
	virtual UBaseStatus* MakeStatusCopy_Implementation(FStatusModifier ExternalModifies, UObject* outer) override;
	virtual void CombineWithStatus_Implementation(UBaseStatus* Status) override;
};
