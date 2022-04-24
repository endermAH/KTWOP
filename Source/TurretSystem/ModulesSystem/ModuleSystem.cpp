// Fill out your copyright notice in the Description page of Project Settings.


#include "ModuleSystem.h"


// Sets default values for this component's properties
UModuleSystem::UModuleSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UModuleSystem::AddStatusesToMap(TMap<TEnumAsByte<EStatusType>, UBaseStatus*>& StatusesMap, UModuleTemplate* Module,
	int Count)
{
	for (auto status: Module->Statuses)
	{
		int cCount = Count;
		auto statusType = status.Status->Execute_GetStatusType(status.Status);
		UBaseStatus* Status;
		if (StatusesMap.Contains(statusType))
		{
			Status = StatusesMap[statusType];
		} else
		{
			cCount--;
			Status = status.Status->MakeStatusCopy(status.BaseModifier, this);
			StatusesMap.Add(statusType, Status);
		}
		auto buff = status.Status->MakeStatusCopy(status.BaseModifier, this);
		for (int i = 0 ; i < cCount; i++)
		{
			Status->CombineWithStatus(buff);
		}
		buff->ConditionalBeginDestroy();
	}
}

void UModuleSystem::AddStatsToTurret(UModuleTemplate* Module, int count)
{
	TurretStatsDelta = TurretStatsDelta + Module->TurretStatsModification*count;
}

// Called when the game starts
void UModuleSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UModuleSystem::AddModule(const FModuleDescription& NewModule)
{
	
	AddedModules.Add(NewModule);
	auto ModuleDescription = ModulesList[NewModule.Module];
	if (IsValid(ModuleDescription))
	{
		if (!ModulesMap.Contains(ModuleDescription))
			ModulesMap.Add(ModuleDescription,0);
		ModulesMap[ModuleDescription]++;
		
		for (auto burenedModule : ModuleDescription->BurnedModules)
		{
			
			if (!ModuleBurnedCount.Contains(burenedModule))
				ModuleBurnedCount.Add(burenedModule,0);
			ModuleBurnedCount[burenedModule]++;
		}
		
	}

	int burnedModulesCount = 0;
	
	for(auto& desc : AddedModules)
	{
		
		if (!ModuleBurnedCount.Contains(desc.Module))
			ModuleBurnedCount.Add(desc.Module,0);
		desc.IsBurned = false; 
		if (ModuleBurnedCount[desc.Module])
		{
			desc.IsBurned = true;
			burnedModulesCount++;
		}
	}

	TurretStatsDelta = FBaseTurretStats(0);
	
	TMap<TEnumAsByte<EStatusType>, UBaseStatus*> StatusesMap;
	AddStatusesToMap(StatusesMap, BurnedModulesReplacer, burnedModulesCount);
	AddStatsToTurret(BurnedModulesReplacer, burnedModulesCount);

	for (auto moduleInt : ModulesMap)
	{
		auto module = moduleInt.Key;
		auto count = moduleInt.Value;
		if (count > 0 && (!IsModuleBurned[module->Type]))
		{
			AddStatusesToMap(StatusesMap, module, count);
			AddStatsToTurret(module, count);
		}
	}

	StatusesMap.GenerateValueArray(Statuses);
}




TArray<FModuleDescription> UModuleSystem::GetAllModules()
{
	return AddedModules;
}

TArray<UBaseStatus*> UModuleSystem::GetAllStatuses()
{
	return Statuses;
}

FBaseTurretStats UModuleSystem::GetTurretStatsDelta()
{
	return TurretStatsDelta;
}

void UModuleSystem::ClearModules()
{
}


// Called every frame
void UModuleSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
