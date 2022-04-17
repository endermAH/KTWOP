#include "BaseStatus.h"

FStatusStats UBaseStatus::ApplyModifiersToStatusStats(const FStatusStats& StatusStats, const FStatusModifier& StatusModifier)
{
	FStatusStats result = StatusStats;
	
	result.Modifier *= StatusModifier.ExternalModifier; 
	result.EffectAccumulationModifier *= StatusModifier.ExternalEffectAccumulationModifier;

	return result;
}

FStatusModifier UBaseStatus::CombineStatusModifier(const FStatusModifier& StatusModifierLeft,
	const FStatusModifier& StatusModifierRight)
{
	FStatusModifier result = StatusModifierLeft;

	result.ExternalModifier*=StatusModifierRight.ExternalModifier;
	result.ExternalEffectAccumulationModifier*=StatusModifierRight.ExternalEffectAccumulationModifier;
	
	return result;
}

void UBaseStatus::Apply_Implementation(ABaseEnemy* enemy, FStatusModifier ExternalModifies)
{
	UE_LOG(LogTemp, Error, TEXT("\"Apply\" method isn't implemented."));
}

void UBaseStatus::AddToBullet_Implementation(AActor* enemy, FStatusModifier ExternalModifies)
{
	UE_LOG(LogTemp, Error, TEXT("\"AddToBullet\" method isn't implemented."));
}

UBaseStatus* UBaseStatus::MakeStatusCopy_Implementation(FStatusModifier ExternalModifies, UObject* outer)
{
	UE_LOG(LogTemp, Error, TEXT("\"MakeStatusCopy\" method isn't implemented."));
	return nullptr;
}
