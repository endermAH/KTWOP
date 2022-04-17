// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDMG.h"

EStatusType UBaseDMG::GetStatusType_Implementation()
{
	return BaseDMG;
}

void UBaseDMG::OnTick_Implementation(const TScriptInterface<IStatusOwner>& statusOwner, float dt)
{}

void UBaseDMG::OnDie_Implementation(const TScriptInterface<IStatusOwner>& statusOwner)
{}

void UBaseDMG::Apply_Implementation(ABaseEnemy* enemy, FStatusModifier ExternalModifies)
{
	if (IsValid(enemy))
	{
		StatusStats = ApplyModifiersToStatusStats(StatusStats, ExternalModifies);
		float dmg = StatusStats.Modifier*StatusStats.Power;
		enemy->ApplyDamage_Implementation( dmg );
		if (IsValid(enemy))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red,
			//    FString::Printf(TEXT("BaseDMG : %f, \n New health : %f"),
			//    	 dmg,  enemy->GetHealth_Implementation()));
		}
	}
	
}

void UBaseDMG::AddToBullet_Implementation(AActor* enemy, FStatusModifier ExternalModifies)
{}



void UBaseDMG::SetDuration_Implementation(float inDuration)
{
	StatusStats.Duration = 0;
}

UBaseStatus* UBaseDMG::MakeStatusCopy_Implementation(FStatusModifier ExternalModifies, UObject* outer)
{
	auto newStatus = NewObject<UBaseDMG>(outer);
	newStatus->StatusStats = ApplyModifiersToStatusStats(StatusStats, ExternalModifies);
	return newStatus;
}
