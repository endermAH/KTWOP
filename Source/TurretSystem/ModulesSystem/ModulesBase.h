#pragma once

#include "CoreMinimal.h"
#include "ModulesBase.generated.h"


UENUM(BlueprintType)
enum EModuleType
{
	VoidModule  UMETA(DisplayName = "VoidModule"),
	RockModule  UMETA(DisplayName = "RockModule"),
};


USTRUCT(BlueprintType)
struct FModuleDescription
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EModuleType> Module;
	// TODO //
	
};
