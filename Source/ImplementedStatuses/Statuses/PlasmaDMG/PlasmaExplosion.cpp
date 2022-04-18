// Fill out your copyright notice in the Description page of Project Settings.


#include "PlasmaExplosion.h"



// Sets default values
APlasmaExplosion::APlasmaExplosion()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetHiddenInGame(false);
	CollisionComponent->SetCollisionProfileName(TEXT("EnemyDestroyer"));
	CollisionComponent->InitSphereRadius(0);
	CollisionComponent->Deactivate();

	ZeroOneCurve.AddKey(0 ,0);
	ZeroOneCurve.AddKey(1 ,1);
	
}

// Called when the game starts or when spawned
void APlasmaExplosion::BeginPlay()
{
	Super::BeginPlay();
}

void APlasmaExplosion::StartExplosion(const FPlasmaExplosionStats& ExplosionStats)
{
	
	FOnTimelineFloat onTimelineCallback;
	FOnTimelineEventStatic onTimelineFinishedCallback;
	
	if (!ExplosionStarted)
	{
		ExplosionStarted = true;
		SavedExplosionStats = ExplosionStats;
		CollisionComponent->Activate();
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APlasmaExplosion::OnBeginOverlap);
		CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &APlasmaExplosion::OnEndOverlap);
		
		ExplosionTimeline = NewObject<UTimelineComponent>(this, FName("ExplosionTimeline"));
		ExplosionTimeline->CreationMethod = EComponentCreationMethod::UserConstructionScript; // Indicate it comes from a blueprint so it gets cleared when we rerun construction scripts
		this->BlueprintCreatedComponents.Add(ExplosionTimeline); // Add to array so it gets saved
		ExplosionTimeline->SetNetAddressable();	// This component has a stable name that can be referenced for replication

		ExplosionTimeline->SetPropertySetObject(this); // Set which object the timeline should drive properties on
		ExplosionTimeline->SetDirectionPropertyName(FName("TimelineDirection"));

		ExplosionTimeline->SetLooping(false);
		ExplosionTimeline->SetTimelineLength(1.0f);
		ExplosionTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
		ExplosionTimeline->SetPlayRate(1.0/ExplosionStats.Duration);

		ExplosionTimeline->SetPlaybackPosition(0.0f, false);

		//Add the float curve to the timeline and connect it to your timelines's interpolation function
		onTimelineCallback.BindDynamic(this, &APlasmaExplosion::TimelineCallback);
		onTimelineFinishedCallback.BindUObject(this, &APlasmaExplosion::EndExplosion);

		auto* curve = NewObject<UCurveFloat>();
		curve->FloatCurve = ZeroOneCurve;
		ExplosionTimeline->AddInterpFloat(curve, onTimelineCallback);
		ExplosionTimeline->SetTimelineFinishedFunc(onTimelineFinishedCallback);

		ExplosionTimeline->RegisterComponent();
		ExplosionTimeline->Play();


		CurrentDamage = SavedExplosionStats.DamageCurveModifier->GetFloatValue(0)*SavedExplosionStats.Damage;
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
			FCollisionShape::MakeSphere(SavedExplosionStats.RadiusCurve->GetFloatValue(0)),
			QueryParams,
			ResponseParams
			);

		for (auto& collision : EnemyOverlaps)
		{
			auto* OtherActor = collision.GetActor();
			if (IsValid(OtherActor) &&
			OtherActor->Implements<UStatusOwner>() &&
			(!DamagedEnemies.Contains(OtherActor)))
				{
					DamagedEnemies.Add(OtherActor);
					IStatusOwner::Execute_ApplyDamage(OtherActor, CurrentDamage);
					if (IsValid(SavedExplosionStats.DamagedEnemyComponent.Get()) &&
						(!IsValid(OtherActor->GetComponentByClass(SavedExplosionStats.DamagedEnemyComponent))))
							OtherActor->AddComponent(FName(FString(TEXT("ExposionComponent"))),
								false, FTransform(),
								SavedExplosionStats.DamagedEnemyComponent);
				}
		}
	}
}

void APlasmaExplosion::EndExplosion_Implementation()
{
	Destroy();
}

void APlasmaExplosion::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called every frame
void APlasmaExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(ExplosionTimeline))
	{
		ExplosionTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}

}


void APlasmaExplosion::TimelineCallback(float Alpha)
{
	float NewRadius = SavedExplosionStats.RadiusCurve->GetFloatValue(Alpha);
	CurrentDamage = SavedExplosionStats.DamageCurveModifier->GetFloatValue(Alpha)*SavedExplosionStats.Damage;
	UpdateRadius(Alpha, NewRadius, CurrentDamage);

	CollisionComponent->SetSphereRadius(NewRadius);
	
	// This function is called for every tick in the timeline.
}



void APlasmaExplosion::OnBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (IsValid(OtherActor) &&
		OtherActor->Implements<UStatusOwner>() &&
		(!DamagedEnemies.Contains(OtherActor)))
	{
		DamagedEnemies.Add(OtherActor);
		IStatusOwner::Execute_ApplyDamage(OtherActor, CurrentDamage);
		if (IsValid(SavedExplosionStats.DamagedEnemyComponent.Get()) &&
			(!IsValid(OtherActor->GetComponentByClass(SavedExplosionStats.DamagedEnemyComponent))))
			OtherActor->AddComponent(FName(FString(TEXT("ExposionComponent"))),
				false, FTransform(),
				SavedExplosionStats.DamagedEnemyComponent);
	}
}

void APlasmaExplosion::OnEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}