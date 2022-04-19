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
	ToxicDMG UMETA(DisplayName = "ToxicDMG"),
	//Ice Status
	IceDMG  UMETA(DisplayName = "IceDMG"),
	
	LightningDMG  UMETA(DisplayName = "LightningDMG"),
	PlasmaDMG  UMETA(DisplayName = "PlasmaDMG"),
	AdditionalSoulsST  UMETA(DisplayName = "AdditionalSoulsDMG"),
	PoolDMG  UMETA(DisplayName = "PoolDMG"),
};



#define TurretEnemyCollisionChannel	ECC_GameTraceChannel1
#define EnemyDestroyerCollisionChannel	ECC_GameTraceChannel2
#define TurretCollisionChannel	ECC_GameTraceChannel3
