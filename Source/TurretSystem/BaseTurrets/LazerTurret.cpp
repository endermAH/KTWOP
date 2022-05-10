

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

void ALazerTurret::RealShoot_Implementation(float DeltaTime)
{
	FVector myPosition = RootComponent->GetComponentLocation();
	FVector enemyPosition =TargetEnemy->GetActorLocation();
	
	Delay -= DeltaTime;
	if ((Delay < 0))
	{
		FBaseBulletStats lazerStats = ModifiedStats.BulletStats;
		FStatusModifier lazerModifier = ModifiedStats.BaseStatusesMultiplier;
		ABaseEnemy* lastHit = nullptr;
		TArray<ABaseEnemy*> VisitedEnemies;
		auto enemy = TargetEnemy;
		float spendDistance = 0;

		while (lazerStats.BounceCount >= 0)
		{
			lazerStats.BounceCount--;
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
			
			for (auto& status :Statuses)
			{
				status->Apply(enemy,ModifiedStats.BaseStatusesMultiplier+lazerModifier);
			}
			
			lazer->Activate();
			if (IsValid(lastHit))
				spendDistance += (lastHit->GetPosition()-enemy->GetPosition()).Size();
			else
				spendDistance += (location-enemy->GetPosition()).Size();

			lazerModifier = UBaseStatus::CombineStatusModifier(
				lazerModifier, lazerStats.BounceModifier);
			lastHit = enemy;
			
			if (lazerStats.BounceCount > 0)
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
					FCollisionShape::MakeSphere(FMath::Max(lazerStats.BounceRadius, lazerStats.MaxFlyDistance - spendDistance)),
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
					
					lazerStats.BounceCount = -1;
				}
			}
		}
		Delay = ModifiedStats.ShootDelay;
	}
}