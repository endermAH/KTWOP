// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBullet.h"

#include "Components/SphereComponent.h"
#include "EnemySystem/Enemy/BaseEnemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
ABaseBullet::ABaseBullet()
{
	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	
	PrimaryActorTick.bCanEverTick = true;
	
	//AbilitySystemComponent = CreateDefaultSubobject<UBulletAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	//AbilitySystemComponent->SetIsReplicated(true);


	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetHiddenInGame(false);
	CollisionComponent->SetCollisionProfileName(TEXT("EnemyDestroyer"));

	
}

// Called when the game starts or when spawned
void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseBullet::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseBullet::OnBeginOverlap);
}

void ABaseBullet::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{



	ABaseEnemy* enemy = Cast<ABaseEnemy>(OtherActor);
	if (IsValid(enemy) && (!VisitedEnemies.Contains(enemy)))
	{
		VisitedEnemies.Add(enemy);
		
		for (auto& status :Statuses)
		{
			status->Apply(enemy, Stats.StatusModifies);
		}
		if (Stats.BulletStats.BounceCount > 0)
		{
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
				FCollisionShape::MakeSphere(FMath::Max(Stats.BulletStats.BounceRadius, Stats.BulletStats.MaxFlyDistance - SpentFlyDistance)),
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
				
				float distance = Stats.BulletStats.MaxFlyDistance - SpentFlyDistance;
				for (auto&  enemyActor : GoodEnemies)
				{
					if ((position-enemyActor->GetPosition()).Size() < distance)
					{
						TargetEnemy = enemyActor;
						foundTarget = true;
						distance = (position-enemyActor->GetPosition()).Size();
					}
				}
			}
			
			if (!foundTarget)
			{
				Stats.BulletStats.BounceCount = 0;
			} else
			{
				Stats.StatusModifies = UBaseStatus::CombineStatusModifier(Stats.StatusModifies,
					Stats.BulletStats.BounceModifier);
				Stats.BulletStats.BounceCount--;
			}
		}
		OnTargetHit(OverlappedComponent, OtherActor, OtherComponent,  OtherBodyIndex, bFromSweep, Hit);
	}
}

void ABaseBullet::StartFly()
{
	CollisionComponent->InitSphereRadius(Stats.BulletRadius);
	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(
		TargetEnemy->GetActorLocation(),
		GetActorLocation() + FVector(0, 0, 0)); // TODO: CRUTCH! I THINK, THAT ENEMY SHOULD PROVIDE IT'S CENTER!!!
	SetActorRotation(rotation);
	IsWorking = true;
}

void ABaseBullet::StopFly()
{
	IsWorking = false;
}

// Called every frame
void ABaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsWorking)
		return;

	
	if (!IsValid(TargetEnemy))
	{
		OnDistanceDeplete();
		return;
	}
	
	FVector targetLocation =  TargetEnemy->GetActorLocation() + FVector(0,0,30);// + TargetEnemy->GetVelocity()*DeltaTime;
	FVector bulletLocation =  RootComponent->GetComponentLocation();
	FVector newLocation = FMath::VInterpTo(
		bulletLocation,
		targetLocation,
		DeltaTime,
		Stats.BulletSpeed
		);
	
	SpentFlyDistance += (bulletLocation - newLocation).Size();

	if (SpentFlyDistance > Stats.BulletStats.MaxFlyDistance)
	{
		OnDistanceDeplete();
		return;
	}
	
	RootComponent->SetWorldLocation(newLocation);
	
}

