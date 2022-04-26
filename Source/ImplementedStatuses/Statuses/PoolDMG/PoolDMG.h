// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoolActor.h"
#include "../ExplodedStatus.h"
#include "PoolDMG.generated.h"

USTRUCT(BlueprintType)
struct FPoolEffectStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FPoolStats PoolStats;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AdditionalModifier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<APoolActor> ExplosionType;
};

/**
 * 
 */
UCLASS()
class IMPLEMENTEDSTATUSES_API UPoolDMG : public UExplodedStatus
{
	GENERATED_BODY()

	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	FPoolEffectStats PoolStats;

	void CreatePool(const TScriptInterface<IStatusOwner>& statusOwner);
	virtual EStatusType GetStatusType_Implementation() override;
	virtual void OnTick_Implementation(const TScriptInterface<IStatusOwner>& statusOwner, float dt) override;
	virtual void Apply_Implementation(ABaseEnemy* enemy, FStatusModifier ExternalModifies) override;
	virtual void AddToBullet_Implementation(AActor* enemy, FStatusModifier ExternalModifies) override;
	virtual void OnDie_Implementation(const TScriptInterface<IStatusOwner>& statusOwner) override;
	
	virtual UBaseStatus* MakeStatusCopy_Implementation(FStatusModifier ExternalModifies, UObject* outer) override;
	virtual void CombineWithStatus_Implementation(UBaseStatus* Status) override;
};
