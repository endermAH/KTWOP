#pragma once

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



UCLASS(Blueprintable, Abstract)
class IMPLEMENTEDSTATUSES_API UBaseStatus : public UDataAsset, public IStatusBase
{
	GENERATED_BODY()

public:



#pragma region StatusStatsFunctions

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FStatusStats ApplyModifiersToStatusStats(const FStatusStats& StatusStats,  const FStatusModifier& StatusModifier);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FStatusStats CombineStatusStats(const FStatusStats& StatusStats1,  const FStatusStats& StatusStats2);


	UFUNCTION(BlueprintCallable, BlueprintPure)
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
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddToBullet(AActor* bullet, FStatusModifier ExternalModifies);
	
	UFUNCTION()
	virtual void AddToBullet_Implementation(AActor* bullet, FStatusModifier ExternalModifies);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UBaseStatus* MakeStatusCopy(FStatusModifier ExternalModifies, UObject* outer);
	
	UFUNCTION()
	virtual UBaseStatus* MakeStatusCopy_Implementation(FStatusModifier ExternalModifies, UObject* outer);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CombineWithStatus(UBaseStatus* Status);
	
	UFUNCTION()
	virtual void CombineWithStatus_Implementation(UBaseStatus* Status);

};

FORCEINLINE FStatusModifier operator+(const FStatusModifier& lhs, const FStatusModifier& rhs){
	return UBaseStatus::CombineStatusModifier(lhs, rhs);
}

FORCEINLINE FStatusModifier operator*(const FStatusModifier& lhs, int32 i){
	FStatusModifier result = lhs;
	for (int k=0; k < i-1; k++)
	{
		result = result + lhs;
	}
	return result;
}