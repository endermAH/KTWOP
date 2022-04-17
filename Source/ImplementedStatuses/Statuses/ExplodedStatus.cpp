// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplodedStatus.h"



void UExplodedStatus::Apply_Implementation(ABaseEnemy* enemy, FStatusModifier ExternalModifies)
{
	Super::Apply_Implementation(enemy, ExternalModifies);
	if (IsValid(enemy))
	{
		auto* existingStatus = Cast<UExplodedStatus>(enemy->Execute_GetStatus(enemy, this->Execute_GetStatusType(this)).GetObject());
		if (IsValid(existingStatus))
		{
			if (!existingStatus->IsExploded)
			{
				StatusStats = ApplyModifiersToStatusStats(StatusStats, ExternalModifies);
				existingStatus->AccumulatedEffect+=
				   StatusStats.EffectAccumulation*StatusStats.EffectAccumulationModifier;
				existingStatus->StatusStats.Modifier =
					FMath::Max(StatusStats.Modifier, existingStatus->StatusStats.Modifier);
				existingStatus->StatusStats.Power =
					FMath::Max(StatusStats.Power, existingStatus->StatusStats.Power);

				if (existingStatus->AccumulatedEffect >= existingStatus->StatusStats.EffectAccumulationMax)
				{
					existingStatus->IsExploded = true;
					IsExploded = true;
					GEngine->AddOnScreenDebugMessage(-1, 1.1f, FColor::Red,
					FString::Printf(TEXT("Effect exploded")
						));
				}
			
				GEngine->AddOnScreenDebugMessage(-1, 1.1f, FColor::Red,
				    FString::Printf(TEXT("EffectAccumulation : %f, \n from : %f"), existingStatus->AccumulatedEffect,
				    	StatusStats.EffectAccumulationMax));
				
			}
		} else
		{
			enemy->AddStatus(this->MakeStatusCopy(ExternalModifies, enemy));
		}
	}
}