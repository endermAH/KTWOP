

#include "LazerTurret.h"

ALazerTurret::ALazerTurret()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ALazerTurret::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALazerTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALazerTurret::Shoot(float DeltaTime)
{
	FVector myPosition = RootComponent->GetComponentLocation();
	FVector enemyPosition =TargetEnemy->GetActorLocation();
	
	Delay -= DeltaTime;
	if ((Delay < 0))
	{
		FLazerStats lazerStats = LazerStats;
		lazerStats.LazerModifier = BaseStats.BaseStatusesMultiplier;
		ABaseEnemy* lastHit = nullptr;
		TArray<ABaseEnemy*> VisitedEnemies;
		auto enemy = TargetEnemy;
		float spendDistance = 0;

		while (lazerStats.LazerBounceCount >= 0)
		{
			lazerStats.LazerBounceCount--;
			FActorSpawnParameters SpawnInfo;
			FVector location;
			if (!IsValid(lastHit))
			{
				location = ArrowComponent->GetComponentLocation();
			}
			else
				location = lastHit->GetPosition();
			
			auto* lazer = GetWorld()->SpawnActor<ABaseLazer>(LazerType, location, FRotator(), SpawnInfo);
			lazer->TargetEnemy = enemy;
			lazer->Stats = lazerStats;
			
			for (auto& status :Statuses)
			{
				status->Apply(enemy,
					UBaseStatus::CombineStatusModifier(BaseStats.BaseStatusesMultiplier, lazerStats.LazerModifier));
			}
			
			lazer->Activate();
			if (IsValid(lastHit))
				spendDistance += (lastHit->GetPosition()-enemy->GetPosition()).Size();
			else
				spendDistance += (location-enemy->GetPosition()).Size();

			lazerStats.LazerModifier = UBaseStatus::CombineStatusModifier(lazerStats.LazerModifier, lazerStats.LazerBounceModifier);
			lastHit = enemy;
			
			if (lazerStats.LazerBounceCount > 0)
			{
				VisitedEnemies.Add(enemy);
				TArray<FOverlapResult> EnemyOverlaps;
				FCollisionQueryParams QueryParams(false);
			
				FCollisionResponseParams ResponseParams;
				ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
				ResponseParams.CollisionResponse.SetResponse(EnemyDestroyerCollisionChannel, ECR_Overlap);
				ResponseParams.CollisionResponse.SetResponse(TurretEnemyCollisionChannel, ECR_Overlap);

				GetWorld()->OverlapMultiByChannel(
					EnemyOverlaps,
					RootComponent->GetComponentLocation(),
					FQuat::Identity,
					EnemyDestroyerCollisionChannel,
					FCollisionShape::MakeSphere(FMath::Max(lazerStats.LazerBounceRadius, lazerStats.MaxFlyDistance - spendDistance)),
					QueryParams,
					ResponseParams
					);

				TArray<ABaseEnemy*> GoodEnemies;
				for (auto& collision : EnemyOverlaps)
				{
					ABaseEnemy* enemyActor = Cast<ABaseEnemy>(collision.GetActor());
					if (IsValid(enemyActor) && (!VisitedEnemies.Contains(enemyActor)))
					{
						GoodEnemies.Add(enemyActor);
					}
				}
			
				bool foundTarget = false;
				if (GoodEnemies.Num() > 0)
				{
					FVector position = RootComponent->GetComponentLocation();
				
					float distance = lazerStats.MaxFlyDistance - spendDistance;
					for (auto&  enemyActor : GoodEnemies)
					{
						if ((position-enemyActor->GetPosition()).Size() < distance)
						{
							enemy = enemyActor;
							foundTarget = true;
							distance = (position-enemyActor->GetPosition()).Size();
						}
					}
				}
			
				if (!foundTarget)
				{
					
					lazerStats.LazerBounceCount = -1;
				}
			}
			
		}
		//FActorSpawnParameters SpawnInfo;
		//FVector location = ArrowComponent->GetComponentLocation();
		//location += ArrowComponent->GetForwardVector() * 30;
		//
		//ABaseBullet* bullet = GetWorld()->SpawnActor<ABaseBullet>(BulletType, location, FRotator(), SpawnInfo);
		//bullet->TargetEnemy = TargetEnemy;
		//bullet->Stats = BaseStats.BulletStats;
		//for (auto& status :Statuses)
		//{
		//	UBaseStatus* copy = status->MakeStatusCopy(BaseStats.BaseStatusesMultiplier, bullet);
		//	bullet->Statuses.Add(copy);
		//}
		//bullet->StartFly();
		//
		//Delay = ShootDelay;
			Delay = ShootDelay;
	}
}