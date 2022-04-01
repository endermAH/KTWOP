#pragma once

#include "CoreMinimal.h"
#include "IStatusData.h"
#include "IStatusOwner.h"
#include "IStatusBase.generated.h"

/**
 * This interface is used by status owners, to apply statuses.
 */
UINTERFACE()
class UStatusBase :  public UStatusData
{
	GENERATED_BODY()
};

class STATUSSYSTEM_API IStatusBase : public IStatusData
{
	GENERATED_BODY()
	
public:
	// Add all necessary status owner events here.
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Apply(const TScriptInterface<IStatusOwner>& statusOwner);

	UFUNCTION()
	virtual void Apply_Implementation(const TScriptInterface<IStatusOwner>& statusOwner);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnTick(const TScriptInterface<IStatusOwner>& statusOwner, float dt);

	UFUNCTION()
	virtual void OnTick_Implementation(const TScriptInterface<IStatusOwner>& statusOwner, float dt);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnDie(const TScriptInterface<IStatusOwner>& statusOwner);

	UFUNCTION()
	virtual void OnDie_Implementation(const TScriptInterface<IStatusOwner>& statusOwner);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TScriptInterface<IStatusBase> MakeStatusCopy(float ExternalModifier, UObject* outer);
	
	UFUNCTION()
	virtual TScriptInterface<IStatusBase> MakeStatusCopy_Implementation(float ExternalModifier, UObject* outer);
};
