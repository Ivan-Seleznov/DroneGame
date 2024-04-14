// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawns/DamageComponent.h"
#include "DroneGameLogs.h"
#include "Pawns/HealthComponent.h"


UDamageComponent::UDamageComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UDamageComponent::ReceiveDamage(float DamageToReceive,AActor* DamageCauser)
{
	if (!HealthComponent)
	{
		DEBUG_LOG("DamageComponent requires HealthComponent")
		return;
	}

	if (DamageCauser)
	{
		LastKnownDamageCauser = DamageCauser;
	}
	HealthComponent->ReduceHealth(DamageToReceive);
}

void UDamageComponent::ReceiveMaxDamage(AActor* DamageCauser)
{
	if (!HealthComponent)
	{
		DEBUG_LOG("DamageComponent requires HealthComponent")
		return;
	}

	if (DamageCauser)
	{
		LastKnownDamageCauser = DamageCauser;
	}
	HealthComponent->ReduceHealth(HealthComponent->GetMaxHealth());
}