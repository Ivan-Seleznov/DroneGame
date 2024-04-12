// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/DamagablePawn.h"
#include "Pawns/DronePawnBase.h"
#include "DronePlayerPawn.generated.h"

class UDroneDamageComponent;
class UHealthComponent;
class UCameraComponent;
class USpringArmComponent;
class UBindInputComponent;


UCLASS()
class DRONEGAME_API ADronePlayerPawn : public ADronePawnBase, public IDamageablePawn
{
	GENERATED_BODY()

public:
	ADronePlayerPawn();
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	virtual void ReceiveDamage(float DamageToReceive) override;
	UFUNCTION(BlueprintCallable)
	virtual UDamageComponent* GetDamageComponent() const override;
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UBindInputComponent> BindInputComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UHealthComponent> HealthComponent;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UDroneDamageComponent> DamageComponent;
};