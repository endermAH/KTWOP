#pragma once

#include "CoreMinimal.h"
#include "IStatusData.h"
#include "IStatusOwner.h"
#include "IStatusBase.generated.h"

/**
 * This interface is used by status owners, to apply statuses.
 */
UINTERFACE()
class UStatusBase : public UStatusData
{
	GENERATED_BODY()
};

class STATUSSYSTEM_API IStatusBase : public IStatusData
{
	GENERATED_BODY()
	
public:
	// Add all necessary status owner events here.
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Apply(TScriptInterface<IStatusOwner>& statusOwner);

	UFUNCTION()
	virtual void Apply_Implementation(TScriptInterface<IStatusOwner>& statusOwner);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnTick(TScriptInterface<IStatusOwner>& statusOwner);

	UFUNCTION()
	virtual void OnTick_Implementation(TScriptInterface<IStatusOwner>& statusOwner);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnDie(TScriptInterface<IStatusOwner>& statusOwner);

	UFUNCTION()
	virtual void OnDie_Implementation(TScriptInterface<IStatusOwner>& statusOwner);
};
