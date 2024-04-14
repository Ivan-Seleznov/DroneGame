// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/HealthComponent.h"

UHealthComponent::UHealthComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SetHealth(DefaultHealth);
}

void UHealthComponent::AddHealth(float HealthToAdd)
{
	if (HealthToAdd > 0.f)
	{
		SetHealth(CurrentHealth + HealthToAdd);
	}
}

void UHealthComponent::ReduceHealth(float HealthToReduce)
{
	if (HealthToReduce > 0.f)
	{
		SetHealth(CurrentHealth - HealthToReduce);
	}
}

float UHealthComponent::GetHealthPercentage() const
{
	if (MaxHealth == 0.f)
	{
		return 0.f;
	}
	
	return CurrentHealth / MaxHealth;
}

void UHealthComponent::SetHealth(float NewHealth)
{
	if (!bEnableHealth)
	{
		return;
	}
	
	const float PrevHealth = CurrentHealth;
	
	CurrentHealth = FMath::Clamp(NewHealth,0.f,MaxHealth);

	if (PrevHealth != CurrentHealth)
	{
		if (OnHealthChangedDelegate.IsBound())
		{
			OnHealthChangedDelegate.Broadcast(PrevHealth,CurrentHealth,this);
		}
	}
	
	if (CurrentHealth <= 0.f)
	{
		bIsOutOfHealth = true;
		if (OnOutOfHealthDelegate.IsBound())
		{
			OnOutOfHealthDelegate.Broadcast(NewHealth,GetPawn<APawn>());
		}
	}
}
