#pragma once

#include "CoreMinimal.h"
#include "KTWOPGameInstance.generated.h"

UCLASS()
class GAMEPLAYSYSTEM_API UKTWOPGameInstance : public UGameInstance {
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Souls;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Stones;

	UFUNCTION(BlueprintCallable)
	void IncreaseSouls(int amount);

	UFUNCTION(BlueprintCallable)
	void DecreaseSouls(int amount);

	UFUNCTION(BlueprintCallable)
	void IncreaseStones(int amount);

	UFUNCTION(BlueprintCallable)
	void DecreaseStones(int amount);
};
