﻿#pragma once

#include "CoreMinimal.h"
#include "EnemySystem/Enemy/BaseEnemy.h"
#include "BaseStatus.generated.h"

USTRUCT(BlueprintType)
struct FStatusModifier
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ExternalModifier = 1.0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ExternalEffectAccumulationModifier = 1.0;
	
};


USTRUCT(BlueprintType)
struct FStatusStats
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Modifier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Power;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Duration;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float EffectAccumulationModifier;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float EffectAccumulationMax;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float EffectAccumulation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UActorComponent> BulletComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UActorComponent> EnemyComponent;

	
};



UCLASS(Blueprintable)
class IMPLEMENTEDSTATUSES_API UBaseStatus : public UDataAsset, public IStatusBase
{
	GENERATED_BODY()

public:



#pragma region StatusStatsFunctions

	UFUNCTION(BlueprintCallable)
	static FStatusStats ApplyModifiersToStatusStats(const FStatusStats& StatusStats,  const FStatusModifier& StatusModifier);
	
	UFUNCTION(BlueprintCallable)
	static FStatusModifier CombineStatusModifier(const FStatusModifier& StatusModifierLeft,  const FStatusModifier& StatusModifierRight);

	virtual float GetModifier_Implementation() override;
	virtual void SetModifier_Implementation(float inModifier) override;
	virtual float GetPower_Implementation() override;
	virtual void SetPower_Implementation(float inPower) override;
	virtual float GetDuration_Implementation() override;
	virtual void SetDuration_Implementation(float inDuration) override;


#pragma endregion 
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	FStatusStats StatusStats;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Apply(ABaseEnemy* enemy, FStatusModifier ExternalModifies);

	UFUNCTION()
	virtual void Apply_Implementation(ABaseEnemy* enemy, FStatusModifier ExternalModifies);
	
	UFUNCTION()
	virtual void AddToBullet_Implementation(AActor* bullet, FStatusModifier ExternalModifies);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UBaseStatus* MakeStatusCopy(FStatusModifier ExternalModifies, UObject* outer);

};
