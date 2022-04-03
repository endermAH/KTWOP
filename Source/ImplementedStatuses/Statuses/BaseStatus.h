#pragma once

#include "CoreMinimal.h"
#include "EnemySystem/Enemy/BaseEnemy.h"
#include "BaseStatus.generated.h"

UCLASS(Blueprintable)
class IMPLEMENTEDSTATUSES_API UBaseStatus : public UObject, public IStatusBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Apply(ABaseEnemy* enemy);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UBaseStatus* MakeStatusCopy(float ExternalModifier, UObject* outer);	
};
