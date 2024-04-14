// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamagablePawn.generated.h"

class UDamageComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageablePawn : public UInterface
{
	GENERATED_BODY()
};

/**
 * Damageable pawn interface
 */
class DRONEGAME_API IDamageablePawn
{
	GENERATED_BODY()

public:
	virtual UDamageComponent* GetDamageComponent() const = 0;

	virtual void ReceiveDamage(float DamageToReceive,AActor* DamageCauser) = 0;
};
