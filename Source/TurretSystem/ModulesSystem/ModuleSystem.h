// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ModulesBase.h"
#include "ImplementedStatuses/Statuses/BaseStatus.h"
#include "StatusSystem/BaseStatuses/StatusType.h"
#include "ModuleSystem.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Abstract)
class TURRETSYSTEM_API UModuleSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UModuleSystem();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<TEnumAsByte<EStatusType>, UBaseStatus*> StatusesList;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void AddModule(const FModuleDescription& NewModule);
	
	UFUNCTION(BlueprintCallable)
	TArray<FModuleDescription> GetAllModules();
	
	UFUNCTION(BlueprintCallable)
	void ClearModules();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
