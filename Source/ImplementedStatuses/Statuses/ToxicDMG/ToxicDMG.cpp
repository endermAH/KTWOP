// Fill out your copyright notice in the Description page of Project Settings.


#include "ToxicDMG.h"

EStatusType UToxicDMG::GetStatusType_Implementation()
{
	return ToxicDMG;
}

void UToxicDMG::OnTick_Implementation(const TScriptInterface<IStatusOwner>& statusOwner, float dt)
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
			statusOwner->Execute_RemoveStatus(statusOwner.GetObject(), ToxicDMG);
		}

		float dmg = StatusStats.Modifier*StatusStats.Power*dt;
		
		if (statusOwner->Execute_IsArmored(statusOwner.GetObject()))
			dmg *= ToxicStats.ArmorDMGMultiplier;
		
		statusOwner->Execute_ApplyDamage(statusOwner.GetObject(), dmg);


		
		ABaseEnemy* enemy = Cast<ABaseEnemy>(statusOwner.GetObject());
		if (IsValid(enemy))
		{
			//GEngine->AddOnScreenDebugMessage(-1, dt, FColor::Red,
			//    FString::Printf(TEXT("ToxicDMG : %f,  New health : %f"),
			//    	 dmg,  enemy->Execute_GetHealth(enemy)));
			//
			//UE_LOG(LogTemp, Error, TEXT("ToxicDMG : %f,  New health : %f"),
			//		 dmg,  enemy->Execute_GetHealth(enemy));
		}
	}
	
}

void UToxicDMG::OnDie_Implementation(const TScriptInterface<IStatusOwner>& statusOwner)
{}

void UToxicDMG::Apply_Implementation(ABaseEnemy* enemy, FStatusModifier ExternalModifies)
{
	Super::Apply_Implementation(enemy, ExternalModifies);
}

void UToxicDMG::AddToBullet_Implementation(AActor* enemy, FStatusModifier ExternalModifies)
{
	Super::AddToBullet_Implementation(enemy, ExternalModifies);
}

UBaseStatus* UToxicDMG::MakeStatusCopy_Implementation(FStatusModifier ExternalModifies, UObject* outer)
{
	auto newStatus = NewObject<UToxicDMG>(outer);
	newStatus->StatusStats = ApplyModifiersToStatusStats(StatusStats, ExternalModifies);
	newStatus->ToxicStats = ToxicStats;
	return newStatus;
}

void UToxicDMG::CombineWithStatus_Implementation(UBaseStatus* Status)
{
	Super::CombineWithStatus_Implementation(Status);
	auto realStatus = Cast<UToxicDMG>(Status);
	if (IsValid(realStatus))
	{
		ToxicStats.ArmorDMGMultiplier = FMath::Max(realStatus->ToxicStats.ArmorDMGMultiplier, ToxicStats.ArmorDMGMultiplier);
	}
}
