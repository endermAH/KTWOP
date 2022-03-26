// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBullet.h"
#include "Components\ArrowComponent.h"
#include "Components\SphereComponent.h"
#include "GameFramework\Actor.h"
#include "TurretSystem\AbilitySystems\TurretAbilitySystemComponent.h"
#include "TurretSystem\Interfaces\IShootable.h"
#include "BaseTurret.generated.h"

#define LATER_SECS(seconds, ...) \
FTimerHandle __tempTimerHandle; \
GetWorldTimerManager().SetTimer(__tempTimerHandle, FTimerDelegate().CreateLambda(__VA_ARGS__), seconds, false);



UCLASS(Abstract)
class TURRETSYSTEM_API ABaseTurret : public AActor, public IShootable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseTurret();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTurretAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UArrowComponent* ArrowComponent;

	UPROPERTY(EditInstanceOnly)
	float TurretRadius;
	
	UPROPERTY(EditInstanceOnly)
	float TurretShootAngle = 1.f/360;
	
	UPROPERTY(EditInstanceOnly)
	float RotationSpeed = 5;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USphereComponent* CollisionComponent;

protected:

	UPROPERTY()
	TSet<APawn*> EnemyActors;
	
	UPROPERTY(BlueprintReadOnly)
	AActor* TargetEnemy;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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


public:
	// Called every frame
	virtual void OnConstruction(const FTransform& Transform) override;
	
	virtual void Tick(float DeltaTime) override;
	
	
};
