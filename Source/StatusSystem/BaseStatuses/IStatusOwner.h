#pragma once

#include "CoreMinimal.h"
#include "IStatusData.h"
#include "UObject/Interface.h"
#include "IStatusOwner.generated.h"

UINTERFACE()
class STATUSSYSTEM_API UStatusOwner : public UInterface
{
	GENERATED_BODY()	
};

class STATUSSYSTEM_API IStatusOwner
{
	GENERATED_BODY()
	
public:
	// Add here desirable tortures for monsters...

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool HasStatus(EStatusType statusType);
	UFUNCTION()
	virtual bool HasStatus_Implementation(EStatusType statusType);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TScriptInterface<IStatusData> GetStatus(EStatusType statusType);
	UFUNCTION()
	virtual TScriptInterface<IStatusData> GetStatus_Implementation(EStatusType statusType);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RemoveStatus(EStatusType statusType);
	UFUNCTION()
	virtual void RemoveStatus_Implementation(EStatusType statusType);

#pragma region Health
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetHealth();
	UFUNCTION()
	virtual float GetHealth_Implementation();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetMaxHealth();
	UFUNCTION()
	virtual float GetMaxHealth_Implementation();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetHealth(float newHealth);
	UFUNCTION()
	virtual void SetHealth_Implementation(float newHealth);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ApplyDamage(float damage);
	UFUNCTION()
	virtual void ApplyDamage_Implementation(float damage);

#pragma endregion


#pragma region Modifiers


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ApplySpeedModifier(float modifier, EStatusType status);
	UFUNCTION()
	virtual void ApplySpeedModifier_Implementation(float modifier, EStatusType status);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ApplyDmgModifier(float modifier, EStatusType status);
	UFUNCTION()
	virtual void ApplyDmgModifier_Implementation(float modifier, EStatusType status);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetSpeedModifier();
	UFUNCTION()
	virtual float GetSpeedModifier_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetDmgModifier();
	UFUNCTION()
	virtual float GetDmgModifier_Implementation();
	
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsArmored();
	UFUNCTION()
	virtual bool IsArmored_Implementation();

#pragma endregion 
	
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnDeath();
};
