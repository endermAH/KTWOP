#pragma once

#include "CoreMinimal.h"
#include "ModulesBase.generated.h"


UENUM(BlueprintType)
enum EStatusModuleType
{
	VoidModule        UMETA(DisplayName = "VoidModule"),
	RockModule        UMETA(DisplayName = "RockModule"),
	ToxicModule       UMETA(DisplayName = "ToxicModule"),
	IceModule         UMETA(DisplayName = "IceModule"),
	LightningModule   UMETA(DisplayName = "LightnibgModule"),
	PlasmaModule      UMETA(DisplayName = "PlasmaModule"),
	SkeletonModule    UMETA(DisplayName = "SkeletonModule"),
	PoolModule        UMETA(DisplayName = "PoolModule"),
};


USTRUCT(BlueprintType)
struct FModuleDescription
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EStatusModuleType> Module;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool IsBurned;
	// TODO //
};
