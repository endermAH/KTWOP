// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components\SphereComponent.h"
#include "Components\TimelineComponent.h"
#include "GameFramework\Actor.h"
#include "ImplementedStatuses\Statuses\BaseStatus.h"
#include "StatusSystem\BaseStatuses\IStatusOwner.h"
#include "StatusSystem\BaseStatuses\StatusType.h"
#include "VapeBullet.generated.h"


USTRUCT(BlueprintType)
struct FVapeBulletStats
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Duration = 2.0;;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RadiusModifier = 1.0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCurveFloat* RadiusCurve;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UActorComponent> DamagedEnemyComponent;

		
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FStatusModifier StatusModifies;
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
};


UCLASS()
class TURRETSYSTEM_API AVapeBullet : public AActor {
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USphereComponent* CollisionComponent;

	UPROPERTY()
	FRichCurve  ZeroOneCurve;
	
	UPROPERTY()
	FVapeBulletStats SavedExplosionStats;
	
	UPROPERTY()
	UTimelineComponent* ExplosionTimeline = nullptr;
	
	UPROPERTY()
	TArray<AActor*> DamagedEnemies;

	UPROPERTY()
	TArray<UBaseStatus*> Statuses;

	
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	
	

	// Sets default values for this actor's properties
	AVapeBullet();

	UPROPERTY(BlueprintReadOnly)
	bool ExplosionStarted = false;

	UFUNCTION(BlueprintCallable)
	void StartExplosion(const TArray<UBaseStatus*>& NewStatuses, FVapeBulletStats ExplosionStats);
	

	UFUNCTION()
	void TimelineCallback(float Alpha);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateRadius(float alpha, float NewRadius);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EndExplosion();
	
	UFUNCTION()
	void EndExplosion_Implementation();
	

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

	void DmgActor(AActor* actor);

};
