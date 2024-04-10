// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/PawnComponent.h"
#include "BindInputComponent.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * BindInputComponent class which sets up input and camera handling for player controlled pawns
 */
UCLASS()
class DRONEGAME_API UBindInputComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	UBindInputComponent(const FObjectInitializer& ObjectInitializer);

	virtual void SetupPlayerInput(UInputComponent* PlayerInputComponent);

protected:
	virtual void Input_Move(const FInputActionValue& Value);
	virtual void Input_Look(const FInputActionValue& Value);
	virtual void Input_Throttle(const FInputActionValue& Value);
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* MoveInputAction;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* LookInputAction;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* ThrottleInputAction;
};
