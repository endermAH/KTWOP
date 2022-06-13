// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseDefines.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "ImplementedStatuses/Statuses/BaseStatus.h"
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
	FStatusModifier StatusModifies;

	
	
};


UCLASS(Abstract)
class TURRETSYSTEM_API ABaseBullet : public AActor
{
	GENERATED_BODY()

private:
	// Sets default values for this actor's properties
	ABaseBullet();

#pragma region BulletStats

	
	UPROPERTY()
	ABaseEnemy* TargetEnemy;
	
	UPROPERTY()
	FBulletStats BulletStats;

	
	UPROPERTY()
	TArray<UBaseStatus*> Statuses;
	

	UPROPERTY()
	TArray<AActor*> VisitedEnemies;

	
	float SpentFlyDistance = 0;

#pragma endregion
public:
	void Init(const TArray<UBaseStatus*>& Statuses, AActor* TargetEnemy, FBaseBulletStats BaseStats, FBulletStats BulletStats);

	UPROPERTY(BlueprintReadOnly)
	bool IsWorking = false;

	UPROPERTY(BlueprintReadWrite)
	FBaseBulletStats BaseStats;

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

	FVector LastDirection;
	
	virtual void Tick(float DeltaTime) override;
};
