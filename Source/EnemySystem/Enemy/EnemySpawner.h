// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemy.h"
#include "UObject/Object.h"
#include "EnemySpawner.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ENEMYSYSTEM_API UEnemySpawner : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ABaseEnemy> EnemyBP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FEnemyStats Stats;

	UFUNCTION(BlueprintCallable)
	ABaseEnemy* SpawnEnemy(AActor* Controller, const FTransform& Transform);
	
};
