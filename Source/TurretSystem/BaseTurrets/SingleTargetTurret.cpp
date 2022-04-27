#include "SingleTargetTurret.h"



ASingleTargetTurret::ASingleTargetTurret()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ASingleTargetTurret::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASingleTargetTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASingleTargetTurret::Shoot(float DeltaTime)
{
	FVector myPosition = RootComponent->GetComponentLocation();
	FVector enemyPosition =TargetEnemy->GetActorLocation();
	
	Delay -= DeltaTime;
	if ((Delay < 0))
	{
		FActorSpawnParameters SpawnInfo;
		FVector location = ArrowComponent->GetComponentLocation();
		
		ABaseBullet* bullet = GetWorld()->SpawnActor<ABaseBullet>(BulletType, location, FRotator(), SpawnInfo);
		
		if (!IsValid(bullet)) {
			UE_LOG(LogTemp, Error, TEXT("Bullet is NULL!"));
			return;
		}
		
		bullet->TargetEnemy = TargetEnemy;
		bullet->Stats.BulletStats = ModifiedStats.BulletStats;
		if (Statuses.Num() == 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1000.f, FColor::Red,
			FString::Printf(TEXT("No statuses in turret. WTF.")));
		}
		for (auto& status :Statuses)
		{
			UBaseStatus* copy = status->MakeStatusCopy(ModifiedStats.BaseStatusesMultiplier, bullet);
			copy->AddToBullet_Implementation(bullet, ModifiedStats.BaseStatusesMultiplier);
			bullet->Statuses.Add(copy);
		}
		bullet->StartFly();
		
		Delay = ModifiedStats.ShootDelay;
	}
}