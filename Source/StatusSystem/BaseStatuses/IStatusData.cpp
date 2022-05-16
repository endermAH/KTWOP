#include "IStatusData.h"

float IStatusData::GetModifier_Implementation()
{
	return 0;
}

void IStatusData::SetModifier_Implementation(float modifier)
{
}

float IStatusData::GetPower_Implementation()
{
	return 0;
}

void IStatusData::SetPower_Implementation(float power)
{
}

float IStatusData::GetDuration_Implementation()
{
	return 0;
}

void IStatusData::SetDuration_Implementation(float duration)
{
}

EStatusType IStatusData::GetStatusType_Implementation()
{
	return Invalid;
}

FVector IPositionedActor::GetLocation_Implementation()
{
	check(false);
	return GetLocation();
}

