// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"
#include "StatusSystem/BaseStatuses/IStatusOwner.h"
#include "GameFramework/Actor.h"
#include "PlasmaExplosion.generated.h"


USTRUCT(BlueprintType)
struct FPlasmaExplosionStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Duration;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCurveFloat* RadiusCurve;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCurveFloat* DamageCurveModifier;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UActorComponent> DamagedEnemyComponent;
	
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
};

UCLASS()
class IMPLEMENTEDSTATUSES_API APlasmaExplosion : public AActor
{
	GENERATED_BODY()
public:

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USphereComponent* CollisionComponent;

	UPROPERTY()
	FRichCurve  ZeroOneCurve;
	
	UPROPERTY()
	FPlasmaExplosionStats SavedExplosionStats;
	
	UPROPERTY()
	UTimelineComponent* ExplosionTimeline = nullptr;

	float CurrentDamage;

	
	UPROPERTY()
	TArray<AActor*> DamagedEnemies;

	
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	
	

	// Sets default values for this actor's properties
	APlasmaExplosion();

	UPROPERTY(BlueprintReadOnly)
	bool ExplosionStarted = false;

	UFUNCTION(BlueprintCallable)
	void StartExplosion(const FPlasmaExplosionStats& ExplosionStats);

	UFUNCTION()
	void TimelineCallback(float Alpha);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateRadius(float alpha, float NewRadius, float Damage);

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

};
