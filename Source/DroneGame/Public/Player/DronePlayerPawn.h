// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/DronePawnBase.h"
#include "DronePlayerPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UBindInputComponent;

UCLASS()
class DRONEGAME_API ADronePlayerPawn : public ADronePawnBase
{
	GENERATED_BODY()

public:
	ADronePlayerPawn();
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UBindInputComponent> BindInputComponent;
};
