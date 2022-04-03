// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components\SphereComponent.h"
#include "GameFramework\Actor.h"
#include "ImplementedStatuses/Statuses/BaseStatus.h"
#include "TurretSystem\AbilitySystems\BulletAbilitySystemComponent.h"
#include "BaseBullet.generated.h"

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

#pragma region BulletStats

	UPROPERTY(BlueprintReadWrite)
	float BulletSpeed = 5;
	
	UPROPERTY(BlueprintReadWrite)
	float MaxFlyDistance = 500;
	
	float SpentFlyDistance = 0;

	UPROPERTY(BlueprintReadOnly)
	TArray<UBaseStatus*> Statuses;

#pragma endregion

	UPROPERTY(BlueprintReadOnly)
	UBulletAbilitySystemComponent* AbilitySystemComponent;

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
