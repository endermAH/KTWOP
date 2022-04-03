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

float IStatusOwner::GetHealth_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("\"GetHealth\" method isn't implemented."));
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

