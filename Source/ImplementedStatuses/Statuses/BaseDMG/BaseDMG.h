// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseStatus.h"
#include "UObject/Object.h"
#include "BaseDMG.generated.h"

/**
 * 
 */
UCLASS()
class IMPLEMENTEDSTATUSES_API UBaseDMG : public UBaseStatus
{
	GENERATED_BODY()
public:
	virtual EStatusType GetStatusType_Implementation() override;
	virtual void OnTick_Implementation(const TScriptInterface<IStatusOwner>& statusOwner, float dt) override;
	virtual void OnDie_Implementation(const TScriptInterface<IStatusOwner>& statusOwner) override;
	virtual void Apply_Implementation(ABaseEnemy* enemy, FStatusModifier ExternalModifies) override;
	virtual void AddToBullet_Implementation(AActor* enemy, FStatusModifier ExternalModifies) override;
	
	virtual void SetDuration_Implementation(float inDuration) override;
	
	virtual UBaseStatus* MakeStatusCopy_Implementation(FStatusModifier ExternalModifies, UObject* outer) override;
};
