// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStatus.h"
#include "ExplodedStatus.h"
#include "LightningDMG.generated.h"

USTRUCT(BlueprintType)
struct FLightningStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MonsterSpeedModifier = 0.;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MonsterDmgModifier = 1.5;
};

/**
 * 
 */
UCLASS()
class IMPLEMENTEDSTATUSES_API ULightningDMG : public UExplodedStatus
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	FLightningStats LightningStats;
	
	float AccumulatedDuration = 0;
	
	virtual EStatusType GetStatusType_Implementation() override;
	virtual void OnTick_Implementation(const TScriptInterface<IStatusOwner>& statusOwner, float dt) override;
	virtual void Apply_Implementation(ABaseEnemy* enemy, FStatusModifier ExternalModifies) override;
	virtual void AddToBullet_Implementation(AActor* enemy, FStatusModifier ExternalModifies) override;
	
	virtual UBaseStatus* MakeStatusCopy_Implementation(FStatusModifier ExternalModifies, UObject* outer) override;
};
