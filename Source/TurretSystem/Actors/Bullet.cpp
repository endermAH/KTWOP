// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "Components\SphereComponent.h"


// Sets default values
ABullet::ABullet()
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
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABullet::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBeginOverlap);
}

void ABullet::OnBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	OnTargetHit(OverlappedComponent, OtherActor, OtherComponent,  OtherBodyIndex, bFromSweep, Hit);
}

void ABullet::StartFly()
{
	IsReady = true;
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsReady)
		return;
	if ((TargetEnemy == nullptr) || (!IsValid(TargetEnemy)))
	{
		this->Destroy();
	}
	
	FVector targetLocation =  TargetEnemy->GetActorLocation() + FVector(0,0,30);
	FVector bulletLocation =  RootComponent->GetComponentLocation();
	FVector newLocation = FMath::VInterpTo(
		bulletLocation,
		targetLocation,
		DeltaTime,
		BulletSpeed
		);
	FlyDistance += (bulletLocation - newLocation).Size();

	if (FlyDistance > MaxFlyDistance)
	{
		OnDistanceDeplete();
	}
	
	RootComponent->SetWorldLocation(newLocation);
	
}

