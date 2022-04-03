#include "BaseStatus.h"

void UBaseStatus::Apply_Implementation(ABaseEnemy* enemy)
{
	UE_LOG(LogTemp, Error, TEXT("\"Apply\" method isn't implemented."));
}

UBaseStatus* UBaseStatus::MakeStatusCopy_Implementation(float ExternalModifier, UObject* outer)
{
	UE_LOG(LogTemp, Error, TEXT("\"MakeStatusCopy\" method isn't implemented."));
	return nullptr;
}
