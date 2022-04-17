// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseDefines.h"
#include "Components\SphereComponent.h"
#include "GameFramework\Actor.h"
#include "ImplementedStatuses/Statuses/BaseStatus.h"
#include "TurretSystem\AbilitySystems\BulletAbilitySystemComponent.h"
#include "BaseBullet.generated.h"

USTRUCT(BlueprintType)
struct FBulletStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BulletSpeed = 5;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BulletRadius = 5;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int BulletBounceCount = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BulletBounceRadius = 1000;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxFlyDistance = 500;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FStatusModifier BulletBounceModifier;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FStatusModifier StatusModifies;
};


UCLASS()
class TURRETSYSTEM_API ABaseBullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseBullet();

	UPROPERTY()
	AActor* TargetEnemy;
	
	UPROPERTY(BlueprintReadOnly)
	bool IsWorking = false;

	UPROPERTY()
	TArray<AActor*> VisitedEnemies;
#pragma region BulletStats
	
	float SpentFlyDistance = 0;

	
	UPROPERTY(BlueprintReadWrite)
	FBulletStats Stats;

	UPROPERTY(BlueprintReadOnly)
	TArray<UBaseStatus*> Statuses;

#pragma endregion

	//UPROPERTY(BlueprintReadOnly)
	//UBulletAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USphereComponent* CollisionComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
	void OnBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& Hit);


	UFUNCTION(BlueprintImplementableEvent)
	void OnTargetHit(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& Hit);

	UFUNCTION(BlueprintImplementableEvent)
	void OnDistanceDeplete();


public:
	// Called every frame

	UFUNCTION(BlueprintCallable)
	void StartFly();
	UFUNCTION(BlueprintCallable)
	void StopFly();


	virtual void Tick(float DeltaTime) override;
};
