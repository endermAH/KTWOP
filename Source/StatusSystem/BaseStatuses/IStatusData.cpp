#include "IStatusData.h"

float IStatusData::GetModifier_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("\"GetModifier\" method isn't implemented."));
	return 0;
}

void IStatusData::SetModifier_Implementation(float modifier)
{
	UE_LOG(LogTemp, Error, TEXT("\"SetModifier\" method isn't implemented."));
}

float IStatusData::GetPower_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("\"GetPower\" method isn't implemented."));
	return 0;
}

void IStatusData::SetPower_Implementation(float power)
{
	UE_LOG(LogTemp, Error, TEXT("\"SetPower\" method isn't implemented."));
}

float IStatusData::GetDuration_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("\"GetDuration\" method isn't implemented."));
	return 0;
}

void IStatusData::SetDuration_Implementation(float duration)
{
	UE_LOG(LogTemp, Error, TEXT("\"SetDuration\" method isn't implemented."));
}

EStatusType IStatusData::GetStatusType_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("\"GetStatus\" method isn't implemented."));
	return Invalid;
}
