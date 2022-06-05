// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"


ABaseEnemy* UEnemySpawner::SpawnEnemy(AActor* Controller, const FTransform& Transform)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = Controller;
	
	ABaseEnemy* enemy = Controller->GetWorld()->SpawnActor<ABaseEnemy>(*EnemyBP, Transform, SpawnInfo);
	enemy->Init(Stats);
	
	return enemy;
}
