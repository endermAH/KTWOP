// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "ImplementedStatuses/Statuses/BaseStatus.h"
#include "PoolActor.generated.h"


USTRUCT(BlueprintType)
struct FPoolStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float Modifier;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Duration;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Radius;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UBaseStatus*> Statuses;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UActorComponent> DamagedEnemyComponent;
	
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
};



UCLASS(BlueprintType)
class IMPLEMENTEDSTATUSES_API APoolActor : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USphereComponent* CollisionComponent;

	UPROPERTY()
	FRichCurve  ZeroOneCurve;
	
	UPROPERTY()
	UTimelineComponent* ExplosionTimeline = nullptr;

	float CurrentDamage;
	
	UPROPERTY()
	TArray<AActor*> DamagedEnemies;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FPoolStats Stats;

	bool IsStarted = false;
public:
	// Sets default values for this actor's properties
	APoolActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable)
	void Start(const FPoolStats& ExplosionStats);

	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
	void TimelineCallback(float Alpha);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Update(float alpha, float Radius);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EndPool();
	
	UFUNCTION()
	void EndPool_Implementation();
	

#pragma region CollisionSystem
	
	UFUNCTION(BlueprintNativeEvent)
	void OnBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& Hit);

	UFUNCTION(BlueprintNativeEvent)
	void OnEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UFUNCTION()
	void OnBeginOverlap_Implementation(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& Hit);

	UFUNCTION()
	void OnEndOverlap_Implementation(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

#pragma endregion 
private:
	void DamageEnemy(ABaseEnemy* enemy);
};
