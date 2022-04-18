// Fill out your copyright notice in the Description page of Project Settings.


#include "LightningDMG.h"

EStatusType ULightningDMG::GetStatusType_Implementation()
{
	return LightningDMG;
}

void ULightningDMG::OnTick_Implementation(const TScriptInterface<IStatusOwner>& statusOwner, float dt)
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
			statusOwner->Execute_RemoveStatus(statusOwner.GetObject(), LightningDMG);
			statusOwner->Execute_ApplyDmgModifier(statusOwner.GetObject(), 1.f, LightningDMG);
			statusOwner->Execute_ApplySpeedModifier(statusOwner.GetObject(), 1.f, LightningDMG);
		}
		


		
		ABaseEnemy* enemy = Cast<ABaseEnemy>(statusOwner.GetObject());
		if (IsValid(enemy))
		{
			GEngine->AddOnScreenDebugMessage(-1, dt, FColor::Red,
			    FString::Printf(TEXT("LightningDMG current dmgM: %f,  current speedM : %f"),
			    	 enemy->GetDmgModifier_Implementation(),  enemy->GetSpeedModifier_Implementation()));
		}
	}
	
}


void ULightningDMG::Apply_Implementation(ABaseEnemy* enemy, FStatusModifier ExternalModifies)
{
	Super::Apply_Implementation(enemy, ExternalModifies);

	if (IsExploded)
	{
		enemy->Execute_ApplyDmgModifier(enemy, LightningStats.MonsterDmgModifier, LightningDMG);
		enemy->Execute_ApplySpeedModifier(enemy, LightningStats.MonsterSpeedModifier, LightningDMG);
	}
}

void ULightningDMG::AddToBullet_Implementation(AActor* enemy, FStatusModifier ExternalModifies)
{
	Super::AddToBullet_Implementation(enemy, ExternalModifies);
}

UBaseStatus* ULightningDMG::MakeStatusCopy_Implementation(FStatusModifier ExternalModifies, UObject* outer)
{
	auto newStatus = NewObject<ULightningDMG>(outer);
	newStatus->StatusStats = ApplyModifiersToStatusStats(StatusStats, ExternalModifies);
	newStatus->LightningStats = LightningStats;
	return newStatus;
}
