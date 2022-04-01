#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "StatusSystem/BaseStatuses/IStatusBase.h"
#include "StatusSystem/BaseStatuses/IStatusOwner.h"
#include "BaseEnemy.generated.h"

UCLASS()
class ENEMYSYSTEM_API ABaseEnemy : public APawn, public IStatusOwner
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxHealth;
	
	UPROPERTY(BlueprintReadWrite)
	int Health;

	ABaseEnemy();
	
	UFUNCTION(BlueprintCallable)
	void AddStatus(TScriptInterface<IStatusBase> status);
	
	virtual void Tick(float DeltaSeconds) override;

#pragma region  IStatusOwner
	
	virtual bool HasStatus_Implementation(EStatusType statusType) override;
	
	virtual TScriptInterface<IStatusData> GetStatus_Implementation(EStatusType statusType) override;
	
	virtual int GetHealth_Implementation() override;
	
	virtual void Damage_Implementation(int damage) override;

#pragma endregion
	
protected:
	UPROPERTY()
	TMap<TEnumAsByte<EStatusType>, TScriptInterface<IStatusBase>> StatusesMap;
};
