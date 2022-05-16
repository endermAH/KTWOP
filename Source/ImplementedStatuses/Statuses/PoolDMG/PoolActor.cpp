// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolActor.h"


// Sets default values
APoolActor::APoolActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APoolActor::BeginPlay()
{
	Super::BeginPlay();
}

void APoolActor::Start(const FPoolStats& ExplosionStats)
{
	FOnTimelineFloat onTimelineCallback;
	FOnTimelineEventStatic onTimelineFinishedCallback;

	if (!IsStarted)
	{
		IsStarted = true;
		Stats = ExplosionStats;
		CollisionComponent->Activate();
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APoolActor::OnBeginOverlap);
		CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &APoolActor::OnEndOverlap);

		ExplosionTimeline = NewObject<UTimelineComponent>(this, FName("ExplosionTimeline"));
		ExplosionTimeline->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		// Indicate it comes from a blueprint so it gets cleared when we rerun construction scripts
		this->BlueprintCreatedComponents.Add(ExplosionTimeline); // Add to array so it gets saved
		ExplosionTimeline->SetNetAddressable();
		// This component has a stable name that can be referenced for replication

		ExplosionTimeline->SetPropertySetObject(this); // Set which object the timeline should drive properties on
		ExplosionTimeline->SetDirectionPropertyName(FName("TimelineDirection"));

		ExplosionTimeline->SetLooping(false);
		ExplosionTimeline->SetTimelineLength(1.0f);
		ExplosionTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
		ExplosionTimeline->SetPlayRate(1.0 / ExplosionStats.Duration);

		ExplosionTimeline->SetPlaybackPosition(0.0f, false);

		//Add the float curve to the timeline and connect it to your timelines's interpolation function
		onTimelineCallback.BindDynamic(this, &APoolActor::TimelineCallback);
		onTimelineFinishedCallback.BindUObject(this, &APoolActor::EndPool);

		auto* curve = NewObject<UCurveFloat>();
		curve->FloatCurve = ZeroOneCurve;
		ExplosionTimeline->AddInterpFloat(curve, onTimelineCallback);
		ExplosionTimeline->SetTimelineFinishedFunc(onTimelineFinishedCallback);

		ExplosionTimeline->RegisterComponent();
		ExplosionTimeline->Play();

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
			FCollisionShape::MakeSphere(Stats.Radius),
			QueryParams,
			ResponseParams);

		for (auto& collision : EnemyOverlaps)
		{
			auto* OtherActor = collision.GetActor();
			if (IsValid(Cast<ABaseEnemy>(OtherActor)))
			{
				DamageEnemy(Cast<ABaseEnemy>(OtherActor));
			}
		}
	}
}

// Called every frame
void APoolActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APoolActor::TimelineCallback(float Alpha)
{
	Update(Alpha, Stats.Radius);
}

void APoolActor::EndPool_Implementation()
{
	Destroy();
}

void APoolActor::OnBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
                                               bool bFromSweep, const FHitResult& Hit)
{
	if (IsValid(Cast<ABaseEnemy>(OtherActor)))
	{
		DamageEnemy(Cast<ABaseEnemy>(OtherActor));
	}
}

void APoolActor::OnEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void APoolActor::DamageEnemy(ABaseEnemy* enemy)
{
	
	if (enemy->Implements<UStatusOwner>() && (!DamagedEnemies.Contains(enemy)))
	{
		DamagedEnemies.Add(enemy);

		for (auto* status : Stats.Statuses )
		{
			status->Apply(enemy,{Stats.Modifier, 1000000});
		}

		if (IsValid(Stats.DamagedEnemyComponent.Get()) &&
			(!IsValid(enemy->GetComponentByClass(Stats.DamagedEnemyComponent))))
			enemy->AddComponent(FName(FString(TEXT("ExposionComponent"))),
			                    false, FTransform(),
			                    Stats.DamagedEnemyComponent);
	}
}
