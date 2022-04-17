// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStatus.h"
#include "ExplodedStatus.h"
#include "UObject\Object.h"
#include "ToxicDMG.generated.h"

USTRUCT(BlueprintType)
struct FToxicStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ArmorDMGMultiplier = 1.5;

	float AccumulatedDuration = 0;
};

/**
 * 
 */
UCLASS()
class IMPLEMENTEDSTATUSES_API UToxicDMG : public UExplodedStatus
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Dafault")
	FToxicStats ToxicStats;
	
	virtual EStatusType GetStatusType_Implementation() override;
	virtual void OnTick_Implementation(const TScriptInterface<IStatusOwner>& statusOwner, float dt) override;
	virtual void OnDie_Implementation(const TScriptInterface<IStatusOwner>& statusOwner) override;
	virtual void Apply_Implementation(ABaseEnemy* enemy, FStatusModifier ExternalModifies) override;
	virtual void AddToBullet_Implementation(AActor* enemy, FStatusModifier ExternalModifies) override;
	
	virtual UBaseStatus* MakeStatusCopy_Implementation(FStatusModifier ExternalModifies, UObject* outer) override;
};
