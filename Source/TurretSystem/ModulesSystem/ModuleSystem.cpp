// Fill out your copyright notice in the Description page of Project Settings.


#include "ModuleSystem.h"


// Sets default values for this component's properties
UModuleSystem::UModuleSystem() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UModuleSystem::AddStatusesToMap(TMap<TEnumAsByte<EStatusType>, UBaseStatus*>& StatusesMap, UModuleTemplate* Module, int Count) {
	if (Count == 0) return;
	for (auto status : Module->Statuses)
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
			Status = status.Status->MakeStatusCopy(ModuleSystemStats.BaseModifier + status.BaseModifier, this);
			StatusesMap.Add(statusType, Status);
		}
		auto buff = status.Status->MakeStatusCopy(ModuleSystemStats.BaseModifier + status.BaseModifier, this);
		for (int i = 0; i < cCount; i++)
		{
			Status->CombineWithStatus(buff);
		}
		buff->ConditionalBeginDestroy();
	}
}

void UModuleSystem::AddStatsToTurret(UModuleTemplate* Module, int count) {
	TurretStatsDelta = TurretStatsDelta + Module->TurretStatsModification * count;
}
void UModuleSystem::BuildModules() {
	ModuleBurnedCount.Empty();

	for (auto& Module : ModulesMap)
	{
		for (auto burenedModule : Module.Key->BurnedModules)
		{
			if (!ModuleBurnedCount.Contains(burenedModule)) ModuleBurnedCount.Add(burenedModule, 0);

			ModuleBurnedCount[burenedModule]++;
		}
	}

	for (auto burenedModule : ModuleSystemStats.BurnedModulesTypes)
	{
		if (!ModuleBurnedCount.Contains(burenedModule)) ModuleBurnedCount.Add(burenedModule, 0);

		ModuleBurnedCount[burenedModule]++;
	}


	int burnedModulesCount = 0;

	for (auto& desc : AddedModules)
	{
		desc.IsBurned = false;

		if (!ModuleBurnedCount.Contains(desc.Module->Type)) ModuleBurnedCount.Add(desc.Module->Type, 0);

		if (ModuleBurnedCount[desc.Module->Type])
		{
			desc.IsBurned = true;
			burnedModulesCount++;
		}
	}

	TurretStatsDelta = FBaseTurretStats(0);

	TMap<TEnumAsByte<EStatusType>, UBaseStatus*> StatusesMap;
	AddStatusesToMap(StatusesMap, ModuleSystemStats.BurnedModulesReplacer, burnedModulesCount);
	AddStatsToTurret(ModuleSystemStats.BurnedModulesReplacer, burnedModulesCount);

	for (auto moduleInt : ModulesMap)
	{
		auto module = moduleInt.Key;
		auto count = moduleInt.Value;
		if (count > 0 && (!ModuleBurnedCount[module->Type]))
		{
			AddStatusesToMap(StatusesMap, module, count);
			AddStatsToTurret(module, count);
		}
	}

	StatusesMap.GenerateValueArray(Statuses);
	WasBuild = true;
}

// Called when the game starts
void UModuleSystem::BeginPlay() {
	Super::BeginPlay();

	// ...
}

void UModuleSystem::AddModule(const FModuleDescription& NewModule) {
	//if (!ModulesList.Contains(NewModule.Module))
	//{
	//	UEnum* MyEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EStatusModuleType"), true);
	//	FString DisplayString = MyEnum->GetNameByValue((int64)NewModule.Module).ToString();
	//	GEngine->AddOnScreenDebugMessage(-1, 1000.f, FColor::Red,
	//		FString::Printf(TEXT("Add %s to Modules map in ModulesSystemBP."), *DisplayString));
	//	return;
	//}


	WasBuild = false;

	auto ModuleDescription = NewModule.Module;

	if (!IsValid(ModuleDescription)) return;

	AddedModules.Add(NewModule);

	if (!ModulesMap.Contains(ModuleDescription)) ModulesMap.Add(ModuleDescription, 0);

	ModulesMap[ModuleDescription]++;
}
void UModuleSystem::AddModules(const TArray<FModuleDescription>& NewModules) {

	for (auto& desc :  NewModules)
		AddModule(desc);
}




TArray<FModuleDescription> UModuleSystem::GetAllModules() {
	if (!WasBuild) BuildModules();
	return AddedModules;
}

TArray<UBaseStatus*> UModuleSystem::GetAllStatuses() {
	if (!WasBuild) BuildModules();
	return Statuses;
}

FBaseTurretStats UModuleSystem::GetTurretStatsDelta() {
	if (!WasBuild) BuildModules();
	return TurretStatsDelta;
}

void UModuleSystem::ClearModules() {
	AddedModules.Empty();
	Statuses.Empty();
	ModuleBurnedCount.Empty();
	ModulesMap.Empty();
	TurretStatsDelta = FBaseTurretStats(0);
}


// Called every frame
void UModuleSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
