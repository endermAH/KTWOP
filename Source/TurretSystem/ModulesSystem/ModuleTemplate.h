// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject\Object.h"
#include "ModulesBase.h"
#include "TurretSystem\BaseDefines.h"
#include "ImplementedStatuses\Statuses\BaseStatus.h"
#include "ModuleTemplate.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FStatusDescription
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FStatusModifier BaseModifier;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBaseStatus* Status;
};


UCLASS(BlueprintType)
class TURRETSYSTEM_API UModuleTemplate : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EStatusModuleType> Type;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TEnumAsByte<EStatusModuleType>>  BurnedModules;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FBaseTurretStats TurretStatsModification = FBaseTurretStats(0);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FStatusDescription>  Statuses;
	
};
