#pragma once

#include "CoreMinimal.h"
#include "ImplementedStatuses/Statuses/BaseStatus.h"
#include "TurretSystem/BaseDefines.h"
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
	TaxModule         UMETA(DisplayName = "TaxModule"),
};




USTRUCT(BlueprintType)
struct FStatusDescription
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FStatusModifier BaseModifier;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBaseStatus* Status;
};


UCLASS(BlueprintType)
class TURRETSYSTEM_API UModuleTemplate : public UDataAsset
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EStatusModuleType> Type;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TEnumAsByte<EStatusModuleType>>  BurnedModules;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FBaseTurretStats TurretStatsModification = FBaseTurretStats(0);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FStatusDescription>  Statuses;

	
};


USTRUCT(BlueprintType)
struct FModuleDescription
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UModuleTemplate* Module;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool IsBurned;
	// TODO //
	
};
