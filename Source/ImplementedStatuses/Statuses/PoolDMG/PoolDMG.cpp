// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolDMG.h"

void UPoolDMG::CreatePool(const TScriptInterface<IStatusOwner>& statusOwner)
{
	FActorSpawnParameters SpawnInfo;

	statusOwner->Execute_RemoveStatus(statusOwner.GetObject(), PoolDMG);

	auto* explosion = GetWorld()->SpawnActor<APoolActor>(
		PoolStats.ExplosionType,
	    statusOwner->
	    Execute_GetLocation(statusOwner.GetObject()), FRotator(),
	    SpawnInfo);
	
	FPoolStats poolStats =PoolStats.PoolStats;
	poolStats.Modifier *= PoolStats.AdditionalModifier;
	
	explosion->Start(poolStats);

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red,
	                                 FString::Printf(TEXT("PoolDMG Create Pool.")
	                                                 ));
}

EStatusType UPoolDMG::GetStatusType_Implementation()
{
	return PoolDMG;
}

void UPoolDMG::OnTick_Implementation(const TScriptInterface<IStatusOwner>& statusOwner, float dt)
{
	if (IsExploded)
	{
		//if (AccumulatedDuration + dt >= StatusStats.Duration)
		//{
		//	dt = StatusStats.Duration - AccumulatedDuration;
		//}
		//AccumulatedDuration += dt;
		//if (AccumulatedDuration + FLT_EPSILON >= StatusStats.Duration)
		//{
		//
		//	IsExploded = false;
		//	StartExplosion(statusOwner);
		//}
	}
}


void UPoolDMG::Apply_Implementation(ABaseEnemy* enemy, FStatusModifier ExternalModifies)
{
	Super::Apply_Implementation(enemy, ExternalModifies);
}

void UPoolDMG::AddToBullet_Implementation(AActor* enemy, FStatusModifier ExternalModifies)
{
	Super::AddToBullet_Implementation(enemy, ExternalModifies);
}

void UPoolDMG::OnDie_Implementation(const TScriptInterface<IStatusOwner>& statusOwner)
{
	if (IsExploded)
	{
		IsExploded = false;
		CreatePool(statusOwner);
	}
}

UBaseStatus* UPoolDMG::MakeStatusCopy_Implementation(FStatusModifier ExternalModifies, UObject* outer)
{
	auto newStatus = NewObject<UPoolDMG>(outer);
	newStatus->StatusStats = ApplyModifiersToStatusStats(StatusStats, ExternalModifies);
	newStatus->PoolStats = PoolStats;
	return newStatus;
}

void UPoolDMG::CombineWithStatus_Implementation(UBaseStatus* Status)
{
	Super::CombineWithStatus_Implementation(Status);
	auto realStatus = Cast<UPoolDMG>(Status);
	if (IsValid(realStatus))
	{
		PoolStats.AdditionalModifier = FMath::Max(realStatus->PoolStats.AdditionalModifier, PoolStats.AdditionalModifier);
	}
}
