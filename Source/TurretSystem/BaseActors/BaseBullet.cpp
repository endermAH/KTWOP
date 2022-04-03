// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBullet.h"

#include "Components\SphereComponent.h"
#include "EnemySystem\Enemy\BaseEnemy.h"


// Sets default values
ABaseBullet::ABaseBullet()
{
	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	
	PrimaryActorTick.bCanEverTick = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<UBulletAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);


	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionComponent->InitSphereRadius(BulletSpeed);
	CollisionComponent->SetCollisionProfileName(TEXT("Pawn"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetHiddenInGame(false);

	
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
	if (IsValid(enemy))
	{
		for (auto& status :Statuses)
		{
			status->Apply(enemy);
		}
		OnTargetHit(OverlappedComponent, OtherActor, OtherComponent,  OtherBodyIndex, bFromSweep, Hit);
	}
}

void ABaseBullet::StartFly()
{
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
		BulletSpeed
		);
	
	SpentFlyDistance += (bulletLocation - newLocation).Size();

	if (SpentFlyDistance > MaxFlyDistance)
	{
		OnDistanceDeplete();
		return;
	}
	
	RootComponent->SetWorldLocation(newLocation);
	
}

