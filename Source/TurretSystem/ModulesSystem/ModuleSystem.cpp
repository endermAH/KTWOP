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


// Called when the game starts
void UModuleSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UModuleSystem::AddModule(const FModuleDescription& NewModule)
{
	
}

TArray<FModuleDescription> UModuleSystem::GetAllModules()
{
	return  {};
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

