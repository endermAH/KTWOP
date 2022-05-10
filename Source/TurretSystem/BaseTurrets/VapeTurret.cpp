// Fill out your copyright notice in the Description page of Project Settings.


#include "VapeTurret.h"


// Sets default values
AVapeTurret::AVapeTurret() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

}

// Called when the game starts or when spawned
void AVapeTurret::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void AVapeTurret::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}
void AVapeTurret::RealShoot_Implementation(float DeltaTime) {

	FActorSpawnParameters Sp;
	auto* vapeBullet =  GetWorld()->SpawnActor<AVapeBullet>(VapeType, ArrowComponent->GetComponentTransform(), Sp);

	TArray<UBaseStatus*> VStatuses;
	for (auto& status :Statuses)
	{
		UBaseStatus* copy = status->MakeStatusCopy(ModifiedStats.BaseStatusesMultiplier, vapeBullet);
		copy->AddToBullet_Implementation(vapeBullet, ModifiedStats.BaseStatusesMultiplier);
		VStatuses.Add(copy);
	}
	
	vapeBullet->StartExplosion(VStatuses, ExplosionStats);
		

	
}

