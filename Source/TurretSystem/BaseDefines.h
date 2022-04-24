#pragma once
#include "ImplementedStatuses\Statuses\BaseStatus.h"
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
		BaseStatusesMultiplier = {1.0};
		BulletStats = {0,0,0,{1,1}};
	};

	FBaseTurretStats operator*(int32 i) const
	{
		auto result = *this;
		result.TurretRadius *=i;
		result.TurretShootAngle *=i;
		result.RotationSpeed *=i;
		result.BulletStats.BounceCount*=i;;
		result.BulletStats.BounceRadius*=i;
		result.BulletStats.MaxFlyDistance*=i;
		
		result.BaseStatusesMultiplier = result.BaseStatusesMultiplier*i;
		result.BulletStats.BounceModifier = result.BulletStats.BounceModifier*i;

		return result;
	}

	FBaseTurretStats operator+(const FBaseTurretStats& rhs) const
	{
		FBaseTurretStats result = *this;
		result.BulletStats					 = BulletStats + rhs.BulletStats;
		result.TurretRadius				     +=rhs.TurretRadius;
		result.TurretShootAngle    		     +=rhs.TurretShootAngle;
		result.RotationSpeed				 +=rhs.RotationSpeed;
		result.BaseStatusesMultiplier        = BaseStatusesMultiplier + rhs.BaseStatusesMultiplier;
		return result;
	};


	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurretRadius = 500.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurretShootAngle = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationSpeed = 5;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatusModifier BaseStatusesMultiplier;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBaseBulletStats BulletStats;
	
};


