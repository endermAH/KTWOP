// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTurret.h"

#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


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
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetHiddenInGame(false);
	CollisionComponent->SetCollisionProfileName(TEXT("Turret"));

	TargetEnemy = nullptr;
}

// Called when the game starts or when spawned
void ABaseTurret::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseTurret::OnBeginOverlap);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseTurret::OnEndOverlap);

	TArray<FOverlapResult> EnemyOverlaps;
	FCollisionQueryParams QueryParams("", false);
			
	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(EnemyDestroyerCollisionChannel, ECR_Overlap);
	ResponseParams.CollisionResponse.SetResponse(TurretEnemyCollisionChannel, ECR_Overlap);

	GetWorld()->OverlapMultiByChannel(
		EnemyOverlaps,
		RootComponent->GetComponentLocation(),
		FQuat::Identity,
		EnemyDestroyerCollisionChannel,
		FCollisionShape::MakeSphere(BaseStats.TurretRadius),
		QueryParams,
		ResponseParams
		);

	for (auto& collision : EnemyOverlaps)
	{
		ABaseEnemy* enemyActor = Cast<ABaseEnemy>(collision.GetActor());
		if (IsValid(enemyActor))
		{
			EnemyActors.Add(enemyActor);
		}
	}
	//TurnOffEvent.AddDynamic(this, &ABaseTurret::TurnOff);
	//TurnOnEvent.AddDynamic(this, &ABaseTurret::TurnOn);
}

void ABaseTurret::OnBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
                                                bool bFromSweep, const FHitResult& Hit)
{
	auto buff = Cast<ABaseEnemy>(OtherActor);
	if (IsValid(buff))
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
				auto buff = Cast<ABaseEnemy>(OtherActor);
				if (buff != nullptr)
					this->EnemyActors.Remove(buff);
	           });
}


void ABaseTurret::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	CollisionComponent->SetSphereRadius(BaseStats.TurretRadius);
}



// Called every frame
void ABaseTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsWorking || !ModifiedStats.CanShoot)
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
			if ((enemyDistance < distance) && (enemyDistance > BaseStats.TurretMinRadius) && (!enemy->IsDead_Implementation()) )
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
		if ((enemyDistance < BaseStats.TurretRadius) && (enemyDistance > BaseStats.TurretMinRadius) && (!TargetEnemy->IsDead_Implementation()))
		{
			auto targetRotator = UKismetMathLibrary::FindLookAtRotation(myPosition, enemyPosition);
			FRotator newRotator = FMath::RInterpTo(RootComponent->GetComponentRotation(),
			                                       targetRotator,
			                                       DeltaTime*BaseStats.RotationSpeed, 1);
			RootComponent->SetWorldRotation(newRotator);
			float angleBetweenTurretAndTarget = FMath::Abs(newRotator.Yaw - targetRotator.Yaw);
			if (angleBetweenTurretAndTarget < BaseStats.TurretShootAngle )
				EventShoot(DeltaTime);
		} else
		{
			TargetEnemy = nullptr;
		}
	}
}
UModuleSystem* ABaseTurret::InitModuleSystem() {
	if (IsValid(ModuleSystemType))
	{
		if (IsValid(ModuleSystemComponent))
		{
			ModuleSystemComponent->DestroyComponent(true);
		}
		
		auto component = AddComponentByClass(ModuleSystemType, false, FTransform::Identity,false);
		component->RegisterComponent();
		ModuleSystemComponent = Cast<UModuleSystem>(component);
	} else
	{
		
		GEngine->AddOnScreenDebugMessage(-1, 1000.f, FColor::Red,
										 FString::Printf(TEXT("Actor %s dont have module system!!!!"),
											 *GetName()));
	}
	
	return ModuleSystemComponent;

		
}

void ABaseTurret::TurnOn()
{
	Statuses = ModuleSystemComponent->GetAllStatuses();
	StatsModification = ModuleSystemComponent->GetTurretStatsDelta();
	ModifiedStats =  BaseStats + StatsModification;
	CollisionComponent->SetSphereRadius(ModifiedStats.TurretRadius);
	IsWorking = true;
	this->BP_TurnOn();
	if (ModifiedStats.CanShoot)
		CollisionComponent->Activate();
	else
		CollisionComponent->Deactivate();
	
	//SetActorTicksEnabled(true/false);
}

void ABaseTurret::TurnOff()
{
	IsWorking = false;
	this->BP_TurnOff();
}

FVector ABaseTurret::GetLocation_Implementation()
{
	return ArrowComponent->GetComponentLocation();
}

