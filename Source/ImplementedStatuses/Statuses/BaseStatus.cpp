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

float UBaseStatus::GetModifier_Implementation() {
	return Modifier;
}

void UBaseStatus::SetModifier_Implementation(float inModifier) {
	Modifier = inModifier;
}

float UBaseStatus::GetPower_Implementation() {
	return Power;
}

void UBaseStatus::SetPower_Implementation(float inPower) {
	Power = inPower;
}

float UBaseStatus::GetDuration_Implementation() {
	return Duration;
}

void UBaseStatus::SetDuration_Implementation(float inDuration) {
	Duration = inDuration;
}
