// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTurret.h"

#include "GameFramework\PawnMovementComponent.h"
#include "Kismet\KismetMathLibrary.h"


// Sets default values
ABaseTurret::ABaseTurret()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));

	//AbilitySystemComponent = CreateDefaultSubobject<UTurretAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	//AbilitySystemComponent->SetIsReplicated(true);


	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward Arrow"));
	ArrowComponent->SetRelativeLocation(FVector(0, 0, 50));
	ArrowComponent->SetHiddenInGame(false);
	ArrowComponent->SetupAttachment(RootComponent);


	// Our root component will be a sphere that reacts to physics
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionComponent->InitSphereRadius(TurretRadius);
	CollisionComponent->SetCollisionProfileName(TEXT("Pawn"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetHiddenInGame(false);

	TargetEnemy = nullptr;
}

// Called when the game starts or when spawned
void ABaseTurret::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseTurret::OnBeginOverlap);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseTurret::OnEndOverlap);
	//TurnOffEvent.AddDynamic(this, &ABaseTurret::TurnOff);
	//TurnOnEvent.AddDynamic(this, &ABaseTurret::TurnOn);
}

void ABaseTurret::OnBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
                                                bool bFromSweep, const FHitResult& Hit)
{
	APawn* buff = Cast<APawn>(OtherActor);
	if (buff != nullptr)
		EnemyActors.Add(buff);
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
	//                                 FString::Printf(TEXT("Add new Actor to pull. Size = %i"), EnemyActors.Num()));
}

void ABaseTurret::OnEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent,
                                              AActor* OtherActor,
                                              UPrimitiveComponent* OtherComp,
                                              int32 OtherBodyIndex)
{
	LATER_SECS(0.2f, [this, OtherActor]()
	           {
				APawn* buff = Cast<APawn>(OtherActor);
				if (buff != nullptr)
					this->EnemyActors.Remove(buff);
	           //GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
		       //    FString::Printf(TEXT("Remove Actor to pull. Size = %i"), EnemyActors.Num()));
	           });
}


void ABaseTurret::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	CollisionComponent->InitSphereRadius(TurretRadius);
}

// Called every frame
void ABaseTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsWorking)
		return;
	
	FVector myPosition = RootComponent->GetComponentLocation();
	myPosition.Z = 0;


	if (!IsValid(TargetEnemy))
	{
		float distance = 10000000;
		for (auto& enemy : EnemyActors)
		{
			if (!IsValid(enemy))
				continue;
			FVector enemyPosition = enemy->GetActorLocation();
			enemyPosition.Z = 0;
			float enemyDistance = (myPosition - enemyPosition).Size();
			if (enemyDistance < distance)
			{
				TargetEnemy = enemy;
				distance = enemyDistance;
			}
		}
	}

	if (IsValid(TargetEnemy))
	{
		
		FVector enemyPosition = TargetEnemy->GetActorLocation();
		enemyPosition.Z = 0;
		float enemyDistance = (myPosition - enemyPosition).Size();
		if (enemyDistance < TurretRadius)
		{
			auto targetRotator = UKismetMathLibrary::FindLookAtRotation(myPosition, enemyPosition);
			FRotator newRotator = FMath::RInterpTo(RootComponent->GetComponentRotation(),
			                                       targetRotator,
			                                       DeltaTime, RotationSpeed);
			RootComponent->SetWorldRotation(newRotator);
			float angleBetweenTurretAndTarget = FMath::Abs((RootComponent->GetComponentRotation() - targetRotator).Vector()|FVector(1,1,1));
			if (angleBetweenTurretAndTarget < TurretShootAngle )
				this->Shoot(DeltaTime);
		} else
		{
			TargetEnemy = nullptr;
		}
	}
}

void ABaseTurret::TurnOn()
{
	IsWorking = true;
	//SetActorTicksEnabled(true/false);
}

void ABaseTurret::TurnOff()
{
	IsWorking = false;
}

