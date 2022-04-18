#pragma once

// Our reflection on the minimum wage...
// Plz, don't forget add new flag for your new status...
UENUM()
enum EStatusType
{
	// Invalid status type.
	Invalid UMETA(DisplayName = "Invalid"),
	// Default damage effect.
	BaseDMG UMETA(DisplayName = "BaseDMG"),
	// Acid damage effect.
	ToxicDMG UMETA(DisplayName = "AcidDMG"),
	//Ice Status
	IceDMG  UMETA(DisplayName = "IceDMG"),
	
	LightningDMG  UMETA(DisplayName = "IceDMG"),
	PlasmaDMG  UMETA(DisplayName = "IceDMG"),
	AdditionalSoulsST  UMETA(DisplayName = "IceDMG"),
	PoolDMG  UMETA(DisplayName = "IceDMG"),
};
