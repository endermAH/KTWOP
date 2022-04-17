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
		ToxicStats.AccumulatedDuration += dt;
		if (ToxicStats.AccumulatedDuration > StatusStats.Duration)
		{
			statusOwner->Execute_RemoveStatus(statusOwner.GetObject(), ToxicDMG);
		}

		float dmg = StatusStats.Modifier*StatusStats.Duration*dt;
		
		if (statusOwner->Execute_IsArmored(statusOwner.GetObject()))
			dmg *= ToxicStats.ArmorDMGMultiplier;
		
		statusOwner->Execute_ApplyDamage(statusOwner.GetObject(), dmg);


		
		ABaseEnemy* enemy = Cast<ABaseEnemy>(statusOwner.GetObject());
		if (IsValid(enemy))
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red,
			    FString::Printf(TEXT("ToxicDMG : %f, \n New health : %f"),
			    	 dmg,  enemy->GetHealth_Implementation()));
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
	
}

UBaseStatus* UToxicDMG::MakeStatusCopy_Implementation(FStatusModifier ExternalModifies, UObject* outer)
{
	auto newStatus = NewObject<UToxicDMG>(outer);
	newStatus->StatusStats = ApplyModifiersToStatusStats(StatusStats, ExternalModifies);
	newStatus->ToxicStats = ToxicStats;
	return newStatus;
}
