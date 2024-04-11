// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputModifiers.h"
#include "RemoveDeltaModifier.generated.h"

/**
 * RemoveDelta modifier class
 */
UCLASS()
class DRONEGAME_API URemoveDeltaModifier : public UInputModifier
{
	GENERATED_BODY()

public:
	virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Scale = 0.01f;
};
