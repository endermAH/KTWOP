#pragma once

#include "CoreMinimal.h"
#include "IStatusData.h"
#include "UObject/Interface.h"
#include "IStatusOwner.generated.h"




UINTERFACE()
class UStatusOwner : public UInterface
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
	void AddStatus(const TScriptInterface<IStatusData>& status);
	UFUNCTION()
	virtual void AddStatus_Implementation(const TScriptInterface<IStatusData>& status);


#pragma region Health
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetHealth();
	UFUNCTION()
	virtual float GetHealth_Implementation();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetHealth(float newHealth);
	UFUNCTION()
	virtual void SetHealth_Implementation(float newHealth);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ApplyDamage(float damage);
	UFUNCTION()
	virtual void ApplyDamage_Implementation(float damage);

#pragma endregion
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnDeath();

};
