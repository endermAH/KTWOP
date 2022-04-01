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

	float Health;
	
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
	int GetHealth();

	UFUNCTION()
	virtual int GetHealth_Implementation();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Damage(int damage);

	UFUNCTION()
	virtual void Damage_Implementation(int damage);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnDeath(int damage);

};
