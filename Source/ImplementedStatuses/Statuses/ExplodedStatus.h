// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStatus.h"
#include "UObject\Object.h"
#include "ExplodedStatus.generated.h"

/**
 * 
 */
UCLASS()
class IMPLEMENTEDSTATUSES_API UExplodedStatus : public UBaseStatus
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool IsExploded = false;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float AccumulatedEffect = 0;

public:
	virtual void Apply_Implementation(ABaseEnemy* enemy, FStatusModifier ExternalModifies) override;
};
