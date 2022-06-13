#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "StatusSystem/BaseStatuses/IStatusOwner.h"
#include "StatusSystem/BaseStatuses/IStatusBase.h"
#include "BaseEnemy.generated.h"

USTRUCT(BlueprintType)
struct FEnemyStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxHealth = 100;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CollisionRadius = 50;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Health = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SpeedModifier = 1;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DmgModifier = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsArmored = false;
};



UCLASS()
class ENEMYSYSTEM_API ABaseEnemy : public APawn, public IStatusOwner
{
	GENERATED_BODY()

public:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USphereComponent* CollisionComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FEnemyStats EnemyStats;

	ABaseEnemy();
	
	UFUNCTION(BlueprintCallable)
	void AddStatus(TScriptInterface<IStatusBase> status);

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Init(const FEnemyStats& Stats);
	
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintImplementableEvent)
	void BP_DamageApplied(float damage, float healthPercent);
	
	UFUNCTION(BlueprintCallable)
	FVector GetPosition();

#pragma region  IStatusOwner
	
	virtual bool HasStatus_Implementation(EStatusType statusType) override;
	virtual void RemoveStatus_Implementation(EStatusType statusType) override;
	
	virtual TScriptInterface<IStatusData> GetStatus_Implementation(EStatusType statusType) override;
	
	virtual float GetHealth_Implementation() override;
	virtual float GetMaxHealth_Implementation() override;
	
	virtual void ApplyDamage_Implementation(float damage) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowApplyedDamage(float damage);

	virtual bool IsArmored_Implementation() override;
	virtual void SetHealth_Implementation(float newHealth) override;
	virtual void ApplySpeedModifier_Implementation(float modifier, EStatusType status) override;
	virtual void ApplyDmgModifier_Implementation(float modifier, EStatusType status) override;
	virtual FVector GetLocation_Implementation() override;

	float HashedSpeedModifier;
	float HashedDmgModifier;
	
	virtual float GetSpeedModifier_Implementation() override;
	virtual float GetDmgModifier_Implementation() override;

#pragma endregion
	
protected:
	UPROPERTY(BlueprintReadWrite)
	TMap<TEnumAsByte<EStatusType>, TScriptInterface<IStatusBase>> StatusesMap;
	UPROPERTY(BlueprintReadWrite)
	TMap<TEnumAsByte<EStatusType>, float> SpeedModifierMap;
	UPROPERTY(BlueprintReadWrite)
	TMap<TEnumAsByte<EStatusType>, float> DmgModifierMap;
	UPROPERTY(BlueprintReadWrite)
	TSet<TEnumAsByte<EStatusType>> RemovedStatuses;
};
