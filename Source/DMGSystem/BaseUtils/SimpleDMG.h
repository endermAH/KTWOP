#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"


#include "SimpleDMG.generated.h"

UENUM(BlueprintType)
enum class DMGType : uint8
{
	FireDMG UMETA(DisplayName="Fire"),
	IceDMG  UMETA(DisplayName="Ice"),
};

USTRUCT(BlueprintType)
struct FSimpleDMG
{
	GENERATED_BODY()

public:
#pragma region ""
	UPROPERTY(BlueprintReadWrite)
	DMGType type;

	UPROPERTY(BlueprintReadWrite)
	float strength;

	
#pragma region METHODS
public:
	FSimpleDMG();


	void DoFoo();
#pragma endregion METHODS
	
};

USTRUCT(BlueprintType)
struct FFullDMG
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	TArray<FSimpleDMG> fullDMG;
};
