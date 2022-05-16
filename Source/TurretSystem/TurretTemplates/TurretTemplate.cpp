// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretTemplate.h"
ABaseTurret* UTurretTemplate::SpawnTurret(AActor* Spawner, const FTransform&, const TArray<FModuleDescription>& Modules) {
	return nullptr;
}

ABaseTurret* USingleTargetTurretTemplate::SpawnTurret(AActor* Spawner, const FTransform& Transform, const TArray<FModuleDescription>& Modules) {

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = Spawner;
	
	ASingleTargetTurret* turret = Spawner->GetWorld()->SpawnActor<ASingleTargetTurret>(TurretBP, Transform, SpawnInfo);
	
	if (!IsValid(turret))
		return nullptr;

	turret->BaseStats = TurretStats;
	turret->BulletType = BulletBP;
	turret->ModuleSystemType = ModuleSystemComponent;
	turret->BulletStats = BulletStats;
	
	auto* ms = turret->InitModuleSystem();
	
	check(IsValid(ms));
	
	ms->ModuleSystemStats = ModuleSystemStats;

	ms->AddModules(Modules);
	return turret;
}
ABaseTurret* ULazerTurretTemplate::SpawnTurret(AActor* Spawner, const FTransform& Transform, const TArray<FModuleDescription>& Modules) {
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = Spawner;
	
	ALazerTurret* turret = Spawner->GetWorld()->SpawnActor<ALazerTurret>(TurretBP, Transform, SpawnInfo);
	
	if (!IsValid(turret))
		return nullptr;

	turret->BaseStats = TurretStats;
	turret->LazerType = LazerBP;
	turret->LazerStats = LazerStats;
	turret->ModuleSystemType = ModuleSystemComponent;
	auto* ms = turret->InitModuleSystem();
	
	check(IsValid(ms));
	
	ms->ModuleSystemStats = ModuleSystemStats;

	ms->AddModules(Modules);
	return turret;
}
ABaseTurret* UVapeTurretTemplate::SpawnTurret(AActor* Spawner, const FTransform& Transform, const TArray<FModuleDescription>& Modules) {
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = Spawner;
	
	AVapeTurret* turret = Spawner->GetWorld()->SpawnActor<AVapeTurret>(TurretBP, Transform, SpawnInfo);
	
	if (!IsValid(turret))
		return nullptr;

	turret->BaseStats = TurretStats;
	turret->VapeType = VapeBP;
	turret->ExplosionStats = VapeStats;
	turret->ModuleSystemType = ModuleSystemComponent;
	auto* ms = turret->InitModuleSystem();
	
	check(IsValid(ms));
	
	ms->ModuleSystemStats = ModuleSystemStats;

	ms->AddModules(Modules);
	return turret;
}
