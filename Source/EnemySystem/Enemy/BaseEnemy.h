#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "StatusSystem\BaseStatuses\IStatusOwner.h"
#include "BaseEnemy.generated.h"

UCLASS()
class ENEMYSYSTEM_API ABaseEnemy : public APawn, public IStatusOwner
{
	GENERATED_BODY()
};
