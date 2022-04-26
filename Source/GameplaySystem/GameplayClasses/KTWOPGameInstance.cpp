#include "KTWOPGameInstance.h"

void UKTWOPGameInstance::IncreaseSouls(int amount)
{
	Souls += amount;
}

void UKTWOPGameInstance::DecreaseSouls(int amount)
{
	Souls -= amount;	
}

void UKTWOPGameInstance::IncreaseStones(int amount)
{
	Stones += amount;
}

void UKTWOPGameInstance::DecreaseStones(int amount)
{
	Stones -= amount;
}
