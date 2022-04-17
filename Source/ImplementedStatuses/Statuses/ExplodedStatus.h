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
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsExploded = false;

public:
	virtual void Apply_Implementation(ABaseEnemy* enemy, FStatusModifier ExternalModifies) override;
};
