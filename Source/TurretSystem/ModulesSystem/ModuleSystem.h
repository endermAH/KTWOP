// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ModulesBase.h"
#include "ImplementedStatuses/Statuses/BaseStatus.h"
#include "StatusSystem/BaseStatuses/StatusType.h"
#include "ModuleSystem.generated.h"

USTRUCT(BlueprintType)
struct FModuleSystemStats {
	GENERATED_BODY()

		
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UModuleTemplate* BurnedModulesReplacer;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TEnumAsByte<EStatusModuleType>> BurnedModulesTypes;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FStatusModifier BaseModifier;
	
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Abstract)
class TURRETSYSTEM_API UModuleSystem : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UModuleSystem();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FModuleSystemStats ModuleSystemStats;
	
	
private:
	bool WasBuild = false;
	
	UPROPERTY()
	TArray<FModuleDescription> AddedModules;
	
	UPROPERTY()
	TArray<UBaseStatus*> Statuses;
	
	UPROPERTY()
	TMap<TEnumAsByte<EStatusModuleType>, int> ModuleBurnedCount;
	
	UPROPERTY()
	TMap<UModuleTemplate*, int> ModulesMap;
	
	UPROPERTY()
	FBaseTurretStats TurretStatsDelta = FBaseTurretStats(0);

	void AddStatusesToMap(TMap<TEnumAsByte<EStatusType>, UBaseStatus*>& StatusesMap, UModuleTemplate* Module, int Count);
	void AddStatsToTurret(UModuleTemplate* Module,  int count);
	void BuildModules();
	
public:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void AddModule(const FModuleDescription& NewModule);
	
	UFUNCTION(BlueprintCallable)
	void AddModules(const TArray<FModuleDescription>& NewModules);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<FModuleDescription> GetAllModules();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UBaseStatus*> GetAllStatuses();
	
	UFUNCTION(BlueprintCallable)
	FBaseTurretStats GetTurretStatsDelta();
	
	UFUNCTION(BlueprintCallable)
	void ClearModules();

	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
