#include "IStatusBase.h"

void IStatusBase::Apply_Implementation(TScriptInterface<IStatusOwner>& statusOwner)
{
	UE_LOG(LogTemp, Error, TEXT("\"Apply\" method isn't implemented."));
}

void IStatusBase::OnTick_Implementation(TScriptInterface<IStatusOwner>& statusOwner)
{
	UE_LOG(LogTemp, Error, TEXT("\"OnTick\" method isn't implemented."));
}

void IStatusBase::OnDie_Implementation(TScriptInterface<IStatusOwner>& statusOwner)
{
	UE_LOG(LogTemp, Error, TEXT("\"OnDie\" method isn't implemented."));
}
