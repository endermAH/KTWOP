#include "BaseEnemy.h"

ABaseEnemy::ABaseEnemy()
{

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetHiddenInGame(false);
	CollisionComponent->SetCollisionProfileName(TEXT("TurretEnemy"));
	CollisionComponent->SetSphereRadius(EnemyStats.CollisionRadius);
}

void ABaseEnemy::AddStatus(TScriptInterface<IStatusBase> status)
{
	// TODO: check, if this status already exist and so on...
	EStatusType type = IStatusBase::Execute_GetStatusType(status.GetObject());
	StatusesMap.Add(type, status);
}

void ABaseEnemy::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	EnemyStats.Health = EnemyStats.MaxHealth;
}

void ABaseEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	TScriptInterface<IStatusOwner> statusOwner;
	statusOwner.SetInterface(this);
	statusOwner.SetObject(this);
	
	for (const auto& pair : StatusesMap)
	{
		IStatusBase::Execute_OnTick(pair.Value.GetObject(), statusOwner, DeltaSeconds);
	}
	for (auto& removedStatus : RemovedStatuses)
	{
		StatusesMap.Remove(removedStatus);
	}
	RemovedStatuses.Empty();
}

FVector ABaseEnemy::GetPosition()
{
	return CollisionComponent->GetComponentLocation();
}

bool ABaseEnemy::HasStatus_Implementation(EStatusType statusType)
{
	return StatusesMap.Contains(statusType);
}

void ABaseEnemy::RemoveStatus_Implementation(EStatusType statusType)
{
	RemovedStatuses.Add(statusType);
}

TScriptInterface<IStatusData> ABaseEnemy::GetStatus_Implementation(EStatusType statusType)
{
	if (StatusesMap.Contains(TEnumAsByte<EStatusType>(statusType)))
	{
		TScriptInterface<IStatusBase>& statusBase = StatusesMap[TEnumAsByte<EStatusType>(statusType)];
		TScriptInterface<IStatusData> statusData;
		statusData.SetInterface(statusBase.GetObject());
		statusData.SetObject(statusBase.GetObject());
		return statusData;
	}
	return nullptr;
}

float ABaseEnemy::GetHealth_Implementation()
{
	return EnemyStats.Health;
}

void ABaseEnemy::ApplyDamage_Implementation(float damage)
{
	EnemyStats.Health = FMath::Clamp<float>(EnemyStats.Health - damage, 0.0f, EnemyStats.MaxHealth);
	TScriptInterface<IStatusOwner> statusOwner;
	statusOwner.SetInterface(this);
	statusOwner.SetObject(this);
	
	if (EnemyStats.Health <= 1)
	{
		for (const TTuple<TEnumAsByte<EStatusType>, TScriptInterface<IStatusBase>>& pair: StatusesMap)
		{
			IStatusBase::Execute_OnDie(pair.Value.GetObject(), statusOwner);
		}
		
		this->Execute_OnDeath(this);
	}
}

bool ABaseEnemy::IsArmored_Implementation()
{
	return EnemyStats.IsArmored;
}
