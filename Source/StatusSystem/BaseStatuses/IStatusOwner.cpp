#include "IStatusOwner.h"

bool IStatusOwner::HasStatus_Implementation(EStatusType statusType)
{
	check(false);
	return false;
}

TScriptInterface<IStatusData> IStatusOwner::GetStatus_Implementation(EStatusType statusType)
{
	check(false);
	return nullptr;
}

void IStatusOwner::RemoveStatus_Implementation(EStatusType statusType)
{
	check(false);
}

float IStatusOwner::GetHealth_Implementation()
{
	check(false);
	return 0;
}

float IStatusOwner::GetMaxHealth_Implementation()
{
	check(false);
	return 0;
}

void IStatusOwner::SetHealth_Implementation(float newHealth)
{
	check(false);
}

void IStatusOwner::ApplyDamage_Implementation(float damage)
{
	check(false);
}

void IStatusOwner::ApplySpeedModifier_Implementation(float damage, EStatusType status)
{
	check(false);
}

void IStatusOwner::ApplyDmgModifier_Implementation(float damage, EStatusType status)
{
	check(false);
}

float IStatusOwner::GetSpeedModifier_Implementation()
{
	check(false);
	return 0;
}

float IStatusOwner::GetDmgModifier_Implementation()
{
	check(false);
	return 0;
}


bool IStatusOwner::IsArmored_Implementation()
{
	check(false);
	return false;
}

bool IStatusOwner::IsDead_Implementation()
{
	check(false);
	return false;
}
