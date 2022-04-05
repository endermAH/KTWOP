#include "BaseEnemy.h"

ABaseEnemy::ABaseEnemy()
{

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetHiddenInGame(false);
	CollisionComponent->SetCollisionProfileName(TEXT("TurretEnemy"));
	CollisionComponent->SetSphereRadius(CollisionRadius);
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

	Health = MaxHealth;
}

void ABaseEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	TScriptInterface<IStatusOwner> statusOwner;
	statusOwner.SetInterface(this);
	statusOwner.SetObject(this);
	
	for (const TTuple<TEnumAsByte<EStatusType>, TScriptInterface<IStatusBase>>& pair : StatusesMap)
	{
		IStatusBase::Execute_OnTick(pair.Value.GetObject(), statusOwner, DeltaSeconds);
	}
}

FVector ABaseEnemy::GetPosition()
{
	return CollisionComponent->GetComponentLocation();
}

bool ABaseEnemy::HasStatus_Implementation(EStatusType statusType)
{
	return StatusesMap.Contains(statusType);
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
	return Health;
}

void ABaseEnemy::ApplyDamage_Implementation(float damage)
{
	Health = FMath::Clamp<float>(Health - damage, 0.0f, MaxHealth);
	TScriptInterface<IStatusOwner> statusOwner;
	statusOwner.SetInterface(this);
	statusOwner.SetObject(this);
	
	if (Health == 0)
	{
		for (const TTuple<TEnumAsByte<EStatusType>, TScriptInterface<IStatusBase>>& pair: StatusesMap)
		{
			IStatusBase::Execute_OnDie(pair.Value.GetObject(), statusOwner);
		}
		
		this->Execute_OnDeath(this);
	}
}