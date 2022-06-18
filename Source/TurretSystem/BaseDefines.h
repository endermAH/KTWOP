#pragma once
#include "ImplementedStatuses/Statuses/BaseStatus.h"
#include "BaseDefines.generated.h"

USTRUCT(BlueprintType)
struct FBaseBulletStats
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int BounceCount = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BounceRadius = 1000;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxFlyDistance = 500;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FStatusModifier BounceModifier;


	FBaseBulletStats operator+(const FBaseBulletStats& rhs) const
	{
		auto result = *this;
		result.BounceCount += rhs.BounceCount;
		result.BounceRadius += rhs.BounceRadius;
		result.MaxFlyDistance += rhs.MaxFlyDistance;
		result.BounceModifier = BounceModifier + rhs.BounceModifier;
		return result;
	}

};

USTRUCT(BlueprintType)
struct FTaxTurretStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool CanProduce = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool CanNotProduce = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SoulsPerTick = 0.0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float StonesPerTick = 0.0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float IncomeModifier = 1.0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TaxTickDelay = 0.0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TaxTickDelayModifier = 1.0;
	
	FTaxTurretStats operator*(int32 i) const
	{
		auto result = *this;
		result.SoulsPerTick   *= i;
		result.StonesPerTick  *= i;
		result.TaxTickDelay   *= i;
		result.IncomeModifier = FMath::Pow(IncomeModifier, i);
		result.TaxTickDelayModifier = FMath::Pow(TaxTickDelayModifier, i);
		return result;
	}

	FTaxTurretStats operator+(const FTaxTurretStats& rhs) const;
};


USTRUCT(BlueprintType)
struct FBaseTurretStats
{
	GENERATED_BODY()
	
public:
	FBaseTurretStats() = default;
	FBaseTurretStats(int32)
	{
		TurretRadius = 0.f;
		TurretShootAngle = 0.f;
		RotationSpeed = 0;
		ShootDelay = 0;
		BaseStatusesMultiplier = {1.0};
		BulletStats = {0,0,0,{1,1}};
	};

	FBaseTurretStats operator*(int32 i) const;

	FBaseTurretStats operator+(const FBaseTurretStats& rhs) const;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool CanShoot = true;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float ShootDelay = 5;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurretRadius = 500.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurretMinRadius = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurretShootAngle = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationSpeed = 5;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatusModifier BaseStatusesMultiplier;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBaseBulletStats BulletStats;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTaxTurretStats  TaxStats;
	
};


