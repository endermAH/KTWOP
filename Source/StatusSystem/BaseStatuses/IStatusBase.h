#pragma once

#include "CoreMinimal.h"
#include "IStatusData.h"
#include "IStatusOwner.h"
#include "IStatusBase.generated.h"

UINTERFACE()
class STATUSSYSTEM_API UStatusBase :  public UStatusData
{
	GENERATED_BODY()
};

class STATUSSYSTEM_API IStatusBase : public IStatusData
{
	GENERATED_BODY()
	
public:
	// Add all necessary status owner events here.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnTick(const TScriptInterface<IStatusOwner>& statusOwner, float dt);
	UFUNCTION()
	virtual void OnTick_Implementation(const TScriptInterface<IStatusOwner>& statusOwner, float dt);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnDie(const TScriptInterface<IStatusOwner>& statusOwner);
	UFUNCTION()
	virtual void OnDie_Implementation(const TScriptInterface<IStatusOwner>& statusOwner);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ApplyDmg(float damage);
	UFUNCTION()
	virtual void ApplyDmg_Implementation(float damage);
};
