// Fill out your copyright notice in the Description page of Project Settings.


#include "PlasmaDMG.h"

void UPlasmaDMG::StartExplosion(const TScriptInterface<IStatusOwner>& statusOwner)
{
	FActorSpawnParameters SpawnInfo;

	statusOwner->Execute_RemoveStatus(statusOwner.GetObject(), PlasmaDMG);
	float dmg = (StatusStats.Power + FMath::Min(CollectedDamage, PlasmaStats.MaxCollectedDmg)) * StatusStats.Modifier;

	auto* explosion = GetWorld()->SpawnActor<APlasmaExplosion>(PlasmaStats.ExplosionType,
	                                                           statusOwner->
	                                                           Execute_GetLocation(statusOwner.GetObject()), FRotator(),
	                                                           SpawnInfo);

	PlasmaStats.ExplosionStats.Damage = dmg;
	explosion->StartExplosion(PlasmaStats.ExplosionStats);

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red,
	                                 FString::Printf(TEXT("PlasmaDMG StartExplosion : %f"),
	                                                 dmg));
}

EStatusType UPlasmaDMG::GetStatusType_Implementation()
{
	return PlasmaDMG;
}

void UPlasmaDMG::OnTick_Implementation(const TScriptInterface<IStatusOwner>& statusOwner, float dt)
{
	if (IsExploded)
	{
		if (AccumulatedDuration + dt >= StatusStats.Duration)
		{
			dt = StatusStats.Duration - AccumulatedDuration;
		}
		AccumulatedDuration += dt;
		if (AccumulatedDuration + FLT_EPSILON >= StatusStats.Duration)
		{

			IsExploded = false;
			StartExplosion(statusOwner);
		}
	}
}


void UPlasmaDMG::Apply_Implementation(ABaseEnemy* enemy, FStatusModifier ExternalModifies)
{
	Super::Apply_Implementation(enemy, ExternalModifies);
	CollectedDamage = 0;
}

void UPlasmaDMG::AddToBullet_Implementation(AActor* enemy, FStatusModifier ExternalModifies)
{
	Super::AddToBullet_Implementation(enemy, ExternalModifies);
}

void UPlasmaDMG::OnDie_Implementation(const TScriptInterface<IStatusOwner>& statusOwner)
{
	if (IsExploded)
	{
		IsExploded = false;
		StartExplosion(statusOwner);
	}
}

void UPlasmaDMG::ApplyDmg_Implementation(float damage)
{
	CollectedDamage += damage*PlasmaStats.CollectedDmgModifier;
}

UBaseStatus* UPlasmaDMG::MakeStatusCopy_Implementation(FStatusModifier ExternalModifies, UObject* outer)
{
	auto newStatus = NewObject<UPlasmaDMG>(outer);
	newStatus->StatusStats = ApplyModifiersToStatusStats(StatusStats, ExternalModifies);
	newStatus->PlasmaStats = PlasmaStats;
	return newStatus;
}

void UPlasmaDMG::CombineWithStatus_Implementation(UBaseStatus* Status)
{
	Super::CombineWithStatus_Implementation(Status);
}
