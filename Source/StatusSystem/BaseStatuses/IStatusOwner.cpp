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

int IStatusOwner::GetHealth_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("\"GetHealth\" method isn't implemented."));
	return Health;
}

void IStatusOwner::Damage_Implementation(int damage)
{
	UE_LOG(LogTemp, Error, TEXT("\"Damage\" method isn't implemented."));
}

