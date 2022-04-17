// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplodedStatus.h"



void UExplodedStatus::Apply_Implementation(ABaseEnemy* enemy, FStatusModifier ExternalModifies)
{
	if (IsValid(enemy))
	{
		auto* existingStatus = Cast<UExplodedStatus>(enemy->Execute_GetStatus(enemy, this->Execute_GetStatusType(this)).GetObject());
		if (IsValid(existingStatus))
		{
			if (!existingStatus->IsExploded)
			{
				StatusStats = ApplyModifiersToStatusStats(StatusStats, ExternalModifies);
				existingStatus->StatusStats.EffectAccumulation+=
				   StatusStats.EffectAccumulation*StatusStats.EffectAccumulationModifier;
				existingStatus->StatusStats.Modifier =
					FMath::Max(StatusStats.Modifier, existingStatus->StatusStats.Modifier);
				existingStatus->StatusStats.Power =
					FMath::Max(StatusStats.Power, existingStatus->StatusStats.Power);

				if (existingStatus->StatusStats.EffectAccumulation >= existingStatus->StatusStats.EffectAccumulationMax)
					existingStatus->IsExploded = true;
			
				GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red,
				    FString::Printf(TEXT("EffectAcc : %f, \n add : %f"), existingStatus->StatusStats.EffectAccumulation,
				    	StatusStats.EffectAccumulation*StatusStats.EffectAccumulationModifier));
				
			}
		} else
		{
			enemy->AddStatus(this->MakeStatusCopy(ExternalModifies, enemy));
		}
	}
}