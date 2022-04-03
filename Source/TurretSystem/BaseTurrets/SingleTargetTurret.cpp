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
	if ((Delay < 0))// && (FVector::DotProduct(UKismetMathLibrary::FindLookAtRotation(myPosition, enemyPosition).Vector(),FVector(1,1,1)) < TurretShootAngle))
	{
		FActorSpawnParameters SpawnInfo;
		FVector location = ArrowComponent->GetComponentLocation();
		location += ArrowComponent->GetForwardVector() * 30;
		
		ABaseBullet* bullet = GetWorld()->SpawnActor<ABaseBullet>(BulletType, location, FRotator(), SpawnInfo);
		bullet->TargetEnemy = TargetEnemy;
		for (auto& status :Statuses)
		{
			UBaseStatus* copy = status->MakeStatusCopy(BaseStatusesMultiplier, bullet);
			bullet->Statuses.Add(copy);
		}
		bullet->StartFly();
		
		Delay = ShootDelay;
	}
}