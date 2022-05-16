// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseDefines.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "ImplementedStatuses/Statuses/BaseStatus.h"
#include "LazerBullet.generated.h"

USTRUCT(BlueprintType)
struct FLazerStats
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float LazerWidth = 5;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float  LazerWidthModifier;
};


UCLASS(Abstract)
class TURRETSYSTEM_API ABaseLazer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseLazer();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	AActor* SorcePActor;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	AActor* TargetEnemy;
	
	UPROPERTY(BlueprintReadOnly)
	bool IsWorking = false;


#pragma region LazerStats
	
	float SpentFlyDistance = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	FLazerStats Stats;

	UPROPERTY(BlueprintReadOnly)
	TArray<UBaseStatus*> Statuses;

#pragma endregion

	//UPROPERTY(BlueprintReadOnly)
	//UBulletAbilitySystemComponent* AbilitySystemComponent;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

public:
	// Called every frame


	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void Activate(const FLazerStats& ViewStats);
};
