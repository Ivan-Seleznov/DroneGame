﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/PawnComponent.h"
#include "Pawns/DronePawnBase.h"
#include "DroneMovementComponent.generated.h"

/**
 * Drone Movement Component class
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DRONEGAME_API UDroneMovementComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	UDroneMovementComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	virtual void AddDroneMovementInput(const FVector& Value);
	UFUNCTION(BlueprintCallable)
    virtual void AddDroneThrottle(float Value);

	virtual void InitDroneMovement(UPrimitiveComponent* InMoveComp,UPhysicsThrusterComponent* InThrusterComp);
	
	void SetComponentToMove(UPrimitiveComponent* InComp);
	void SetThrusterComponent(UPhysicsThrusterComponent* InComp);

	UFUNCTION(BlueprintPure)
	float GetThrottlePercent() const;
	
protected:
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float RotationSpeed = 400.f;
	
	
	UPROPERTY(BlueprintReadOnly)
	float CurrentThrottle;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float ThrottleSpeed = 100.f;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float MinThrottle = -200.f;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float MaxThrottle = 200.f;
	
private:
	UPROPERTY()
	UPrimitiveComponent* ComponentToMove;

	UPROPERTY()
	UPhysicsThrusterComponent* ThrusterComponent;

	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess))
	float ThrottleInput;
	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess))
	FVector MoveInput;
};
