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

float UBaseStatus::GetModifier_Implementation()
{
	return StatusStats.Modifier;
}

void UBaseStatus::SetModifier_Implementation(float inModifier)
{
	StatusStats.Modifier = inModifier;
}

float UBaseStatus::GetPower_Implementation()
{
	return StatusStats.Power;
}

void UBaseStatus::SetPower_Implementation(float inPower)
{
	StatusStats.Power = inPower;
}

float UBaseStatus::GetDuration_Implementation()
{
	return StatusStats.Duration;
}

void UBaseStatus::SetDuration_Implementation(float inDuration)
{
	StatusStats.Duration = (inDuration);
}

void UBaseStatus::Apply_Implementation(ABaseEnemy* enemy, FStatusModifier ExternalModifies)
{
	if (IsValid(StatusStats.EnemyComponent.Get()))
	{
		auto component = enemy->GetComponentByClass(StatusStats.EnemyComponent);
		if (!IsValid(component))
			enemy->AddComponent(FName(FString::Printf(TEXT("Status_%i"), (int32)this->GetStatusType_Implementation())),
				false, FTransform(),
				StatusStats.EnemyComponent);
	}
}

void UBaseStatus::AddToBullet_Implementation(AActor* bullet, FStatusModifier ExternalModifies)
{
	if (IsValid(StatusStats.BulletComponent.Get()))
	{
		auto component = bullet->GetComponentByClass(StatusStats.BulletComponent);
		if (!IsValid(component))
			bullet->AddComponent(FName(FString::Printf(TEXT("Status_%i"), (int32)this->GetStatusType_Implementation())),
				false, FTransform(),
				StatusStats.BulletComponent);
	}
}

UBaseStatus* UBaseStatus::MakeStatusCopy_Implementation(FStatusModifier ExternalModifies, UObject* outer)
{
	return nullptr;
}
