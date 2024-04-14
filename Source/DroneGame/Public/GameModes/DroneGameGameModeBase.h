// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DroneGameGameModeBase.generated.h"


class ADronePlayerPawn;
/**
 * DroneGame Base GameMode class 
 */
UCLASS()
class DRONEGAME_API ADroneGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	APawn* RespawnPawn();
private:
	UPROPERTY()
	TArray<AActor*> PlayerStarts;
};
