// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawns/DamageComponent.h"
#include "DroneGameLogs.h"
#include "Pawns/HealthComponent.h"


UDamageComponent::UDamageComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UDamageComponent::ReceiveDamage(float DamageToReceive)
{
	if (!HealthComponent)
	{
		DEBUG_LOG("DamageComponent requires HealthComponent")
		return;
	}
	
	HealthComponent->ReduceHealth(DamageToReceive);
}

void UDamageComponent::ReceiveMaxDamage()
{
	if (!HealthComponent)
	{
		DEBUG_LOG("DamageComponent requires HealthComponent")
		return;
	}

	HealthComponent->ReduceHealth(HealthComponent->GetMaxHealth());
}