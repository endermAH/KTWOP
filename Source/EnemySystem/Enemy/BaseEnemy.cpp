#include "BaseEnemy.h"

ABaseEnemy::ABaseEnemy()
	: Health(MaxHealth)
{}

void ABaseEnemy::AddStatus(TScriptInterface<IStatusBase> status) {
	// TODO: check, if this status already exist and so on...
	EStatusType type = IStatusBase::Execute_GetStatusType(status.GetObject());
	StatusesMap.Add(type, status);
}

void ABaseEnemy::Tick(float DeltaSeconds)
{
	TScriptInterface<IStatusOwner> statusOwner;
	statusOwner.SetInterface(this);
	statusOwner.SetObject(this);
	
	for (const TTuple<TEnumAsByte<EStatusType>, TScriptInterface<IStatusBase>>& pair : StatusesMap) {
		IStatusBase::Execute_OnTick(pair.Value.GetObject(), statusOwner, DeltaSeconds);
	}
}

bool ABaseEnemy::HasStatus_Implementation(EStatusType statusType)
{
	return StatusesMap.Contains(statusType);
}

TScriptInterface<IStatusData> ABaseEnemy::GetStatus_Implementation(EStatusType statusType)
{
	TScriptInterface<IStatusBase> statusBase = StatusesMap[TEnumAsByte<EStatusType>(statusType)];
	TScriptInterface<IStatusData> statusData;
	statusData.SetInterface(statusBase.GetObject());
	statusData.SetObject(statusBase.GetObject());
	return statusData;
}

int ABaseEnemy::GetHealth_Implementation()
{
	return Health;
}

void ABaseEnemy::Damage_Implementation(int damage)
{
	Health = FMath::Clamp(Health - damage, 0, MaxHealth);
	TScriptInterface<IStatusOwner> statusOwner;
	statusOwner.SetInterface(this);
	statusOwner.SetObject(this);
	
	if (Health == 0) {
		for (const auto& pair : StatusesMap) {
			pair.Value->OnDie(statusOwner);
		}
	}
}
