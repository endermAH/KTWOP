#include "BaseDefines.h"

FTaxTurretStats FTaxTurretStats::operator+(const FTaxTurretStats& rhs) const
{
	auto result = *this;
	result.SoulsPerTick += rhs.SoulsPerTick;
	result.StonesPerTick += rhs.StonesPerTick;
	result.TaxTickDelay += rhs.TaxTickDelay;
	result.IncomeModifier = IncomeModifier * rhs.IncomeModifier;
	result.TaxTickDelayModifier = TaxTickDelayModifier * rhs.TaxTickDelayModifier;
	result.CanProduce |= rhs.CanProduce;
	result.CanNotProduce |= rhs.CanNotProduce;
	return result;
}

FBaseTurretStats FBaseTurretStats::operator*(int32 i) const
{
	auto result = *this;
	result.TurretRadius *=i;
	result.TurretShootAngle *=i;
	result.RotationSpeed *=i;
	result.BulletStats.BounceCount*=i;;
	result.BulletStats.BounceRadius*=i;
	result.BulletStats.MaxFlyDistance*=i;
	result.ShootDelay *= i;
		
	result.BaseStatusesMultiplier = result.BaseStatusesMultiplier*i;
	result.BulletStats.BounceModifier = result.BulletStats.BounceModifier*i;

	result.TaxStats = result.TaxStats*i;

	return result;
}

FBaseTurretStats FBaseTurretStats::operator+(const FBaseTurretStats& rhs) const
{
	FBaseTurretStats result = *this;
	result.BulletStats					 = BulletStats + rhs.BulletStats;
	result.TaxStats					     = TaxStats + rhs.TaxStats;
	result.TurretRadius				    += rhs.TurretRadius;
	result.TurretShootAngle    		    += rhs.TurretShootAngle;
	result.RotationSpeed				+= rhs.RotationSpeed;
	result.ShootDelay				    += rhs.ShootDelay;
	result.BaseStatusesMultiplier        = BaseStatusesMultiplier + rhs.BaseStatusesMultiplier;
	result.CanShoot						&= rhs.CanShoot;
	return result;
};