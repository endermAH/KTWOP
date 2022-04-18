#include "IStatusOwner.h"

bool IStatusOwner::HasStatus_Implementation(EStatusType statusType)
{
	UE_LOG(LogTemp, Error, TEXT("\"GetPower\" method isn't implemented."));
	return false;
}

TScriptInterface<IStatusData> IStatusOwner::GetStatus_Implementation(EStatusType statusType)
{
	UE_LOG(LogTemp, Error, TEXT("\"GetStatus\" method isn't implemented."));
	return nullptr;
}

void IStatusOwner::RemoveStatus_Implementation(EStatusType statusType)
{
	UE_LOG(LogTemp, Error, TEXT("\"RemoveStatus\" method isn't implemented."));
}

float IStatusOwner::GetHealth_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("\"GetHealth\" method isn't implemented."));
	return 0;
}

float IStatusOwner::GetMaxHealth_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("\"GetMaxHealth\" method isn't implemented."));
	return 0;
}

void IStatusOwner::SetHealth_Implementation(float newHealth)
{
	UE_LOG(LogTemp, Error, TEXT("\"SetHealth\" method isn't implemented."));
}

void IStatusOwner::ApplyDamage_Implementation(float damage)
{
	UE_LOG(LogTemp, Error, TEXT("\"ApplyDamage\" method isn't implemented."));
}

void IStatusOwner::ApplySpeedModifier_Implementation(float damage, EStatusType status)
{
	UE_LOG(LogTemp, Error, TEXT("\"ApplySpeedModifier\" method isn't implemented."));
}

void IStatusOwner::ApplyDmgModifier_Implementation(float damage, EStatusType status)
{
	UE_LOG(LogTemp, Error, TEXT("\"ApplyDmgModifier\" method isn't implemented."));
}

float IStatusOwner::GetSpeedModifier_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("\"GetSpeedModifier\" method isn't implemented."));
	return 0;
}

float IStatusOwner::GetDmgModifier_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("\"GetSpeedModifier\" method isn't implemented."));
	return 0;
}


bool IStatusOwner::IsArmored_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("\"IsArmored\" method isn't implemented."));
	return false;
}

FVector IStatusOwner::GetLocation_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("\"GetLocation\" method isn't implemented."));
	return FVector();
}

