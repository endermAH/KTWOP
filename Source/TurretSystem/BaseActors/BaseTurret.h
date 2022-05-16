// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBullet.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "TurretSystem/Interfaces/IShootable.h"
#include "TurretSystem/ModulesSystem/ModuleSystem.h"
#include "BaseTurret.generated.h"

#define LATER_SECS(seconds, ...) \
FTimerHandle __tempTimerHandle; \
GetWorldTimerManager().SetTimer(__tempTimerHandle, FTimerDelegate().CreateLambda(__VA_ARGS__), seconds, false);


//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVoidDelegate);



UCLASS(Abstract)
class TURRETSYSTEM_API ABaseTurret : public AActor, public IShootable, public IPositionedActor
{
	GENERATED_BODY()
private:
	
public:
	// Sets default values for this actor's properties
	ABaseTurret();

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//UTurretAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UArrowComponent* ArrowComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USphereComponent* CollisionComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UModuleSystem* ModuleSystemComponent;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UModuleSystem> ModuleSystemType = nullptr;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FModuleSystemStats ModuleSystemStats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats")
	FBaseTurretStats BaseStats;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Stats")
	FBaseTurretStats ModifiedStats;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats")
	FBaseTurretStats StatsModification;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Stats")
	TArray<UBaseStatus*> Statuses;
protected:

	UPROPERTY()
	TSet<ABaseEnemy*> EnemyActors;
	
	UPROPERTY(BlueprintReadOnly)
	ABaseEnemy* TargetEnemy;
	
	
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

	UFUNCTION(BlueprintCallable)
	UModuleSystem* InitModuleSystem();

	UFUNCTION(BlueprintImplementableEvent)
	void EventShoot(float DeltaTime);

#pragma region TurnOnOffSystem
public:
	UFUNCTION(BlueprintCallable)
	void TurnOn();
	UFUNCTION(BlueprintCallable)
	void TurnOff();
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool IsWorking = false;
private:

#pragma endregion


	FVector GetLocation_Implementation() override;
};
