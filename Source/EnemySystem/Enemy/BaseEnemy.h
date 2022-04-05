#pragma once

#include "CoreMinimal.h"
#include "Components\SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "StatusSystem/BaseStatuses/IStatusOwner.h"
#include "StatusSystem/BaseStatuses/IStatusBase.h"
#include "BaseEnemy.generated.h"

UCLASS()
class ENEMYSYSTEM_API ABaseEnemy : public APawn, public IStatusOwner
{
	GENERATED_BODY()

public:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USphereComponent* CollisionComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxHealth;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CollisionRadius;
	
	UPROPERTY(BlueprintReadWrite)
	float Health;

	ABaseEnemy();
	
	UFUNCTION(BlueprintCallable)
	void AddStatus(TScriptInterface<IStatusBase> status);

	virtual void OnConstruction(const FTransform& Transform) override;
	
	virtual void Tick(float DeltaSeconds) override;


	
	UFUNCTION(BlueprintCallable)
	FVector GetPosition();

#pragma region  IStatusOwner
	
	virtual bool HasStatus_Implementation(EStatusType statusType) override;
	
	virtual TScriptInterface<IStatusData> GetStatus_Implementation(EStatusType statusType) override;
	
	virtual float GetHealth_Implementation() override;
	
	virtual void ApplyDamage_Implementation(float damage) override;

#pragma endregion
	
protected:
	UPROPERTY(BlueprintReadWrite)
	TMap<TEnumAsByte<EStatusType>, TScriptInterface<IStatusBase>> StatusesMap;
};
