#include "BaseStatus.h"

FStatusStats UBaseStatus::ApplyModifiersToStatusStats(const FStatusStats& StatusStats, const FStatusModifier& StatusModifier)
{
	FStatusStats result = StatusStats;
	
	result.Modifier *= StatusModifier.ExternalModifier; 
	result.EffectAccumulationModifier *= StatusModifier.ExternalEffectAccumulationModifier;

	return result;
}

FStatusStats UBaseStatus::CombineStatusStats(const FStatusStats& StatusStats1, const FStatusStats& StatusStats2)
{
	FStatusStats result;

	result.Duration =					FMath::Max(StatusStats1.Duration, StatusStats2.Duration);
	result.Modifier =					FMath::Max(StatusStats1.Modifier, StatusStats2.Modifier);
	result.Power =						StatusStats1.Power + StatusStats2.Power*StatusStats2.Modifier/StatusStats1.Modifier;
	result.EffectAccumulation = 		StatusStats1.EffectAccumulation + StatusStats2.EffectAccumulation;
	result.EffectAccumulationMax = 		FMath::Min(StatusStats1.EffectAccumulationMax, StatusStats2.EffectAccumulationMax);
	result.EffectAccumulationModifier = FMath::Max(StatusStats1.EffectAccumulationModifier, StatusStats2.EffectAccumulationModifier);
	result.BulletComponent =			StatusStats1.BulletComponent;
	result.EnemyComponent =				StatusStats1.EnemyComponent;
	
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
		{
			auto c = enemy->AddComponentByClass(
				*StatusStats.EnemyComponent,
				false, FTransform(),
				false);
			
			c->RegisterComponent();
		}
	}
}

void UBaseStatus::AddToBullet_Implementation(AActor* bullet, FStatusModifier ExternalModifies)
{
	if (IsValid(StatusStats.BulletComponent.Get()))
	{
		auto component = bullet->GetComponentByClass(StatusStats.BulletComponent);
		if (!IsValid(component))
		{
			auto c = bullet->AddComponentByClass(
				*StatusStats.BulletComponent,
				false, FTransform(),
				false);
			
			c->RegisterComponent();
		}
	}
}

UBaseStatus* UBaseStatus::MakeStatusCopy_Implementation(FStatusModifier ExternalModifies, UObject* outer)
{
	return nullptr;
}

void UBaseStatus::CombineWithStatus_Implementation(UBaseStatus* Status)
{
	this->StatusStats = CombineStatusStats(this->StatusStats, Status->StatusStats);
}
