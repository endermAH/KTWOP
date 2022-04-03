#pragma once

#include "CoreMinimal.h"
#include "EnemySystem/Enemy/BaseEnemy.h"
#include "BaseStatus.generated.h"

UCLASS(Blueprintable)
class IMPLEMENTEDSTATUSES_API UBaseStatus : public UObject, public IStatusBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintGetter=GetModifier_Implementation, BlueprintSetter=SetModifier_Implementation, BlueprintReadWrite)
	float Modifier;

	UPROPERTY(BlueprintGetter=GetPower_Implementation, BlueprintSetter=SetPower_Implementation, BlueprintReadWrite)
	float Power;

	UPROPERTY(BlueprintGetter=GetDuration_Implementation, BlueprintSetter=SetDuration_Implementation, BlueprintReadWrite)
	float Duration;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Apply(ABaseEnemy* enemy);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UBaseStatus* MakeStatusCopy(float ExternalModifier, UObject* outer);

#pragma region IStatusBase
	
	UFUNCTION(BlueprintGetter)
	virtual float GetModifier_Implementation() override;	
	UFUNCTION(BlueprintSetter)
	virtual void SetModifier_Implementation(float inModifier) override;

	UFUNCTION(BlueprintGetter)
	virtual float GetPower_Implementation() override;
	UFUNCTION(BlueprintSetter)
	virtual void SetPower_Implementation(float inPower) override;

	UFUNCTION(BlueprintGetter)
	virtual float GetDuration_Implementation() override;
	UFUNCTION(BlueprintSetter)
	virtual void SetDuration_Implementation(float inDuration) override;

#pragma endregion 
};
