// Fill out your copyright notice in the Description page of Project Settings.


#include "FireSystem/FireComponentBase.h"
#include "DroneGameLogs.h"

UFireComponentBase::UFireComponentBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UFireComponentBase::Fire(const FVector& StartLocation, const FVector& Direction)
{
}

void UFireComponentBase::BeginPlay()
{
	Super::BeginPlay();
}

bool UFireComponentBase::CanFire() const
{
	return IsFireRateValid();
}

bool UFireComponentBase::IsFireRateValid() const
{
	return GetCurrentFireRate() <= FireRate;
}

float UFireComponentBase::GetCurrentFireRate() const
{
	const float CurrentFireRate =  1 / GetTimeSinceLastFired();
	DEBUG_LOG("CurrentFireRate: %f",CurrentFireRate);
	return CurrentFireRate;
}

float UFireComponentBase::GetTimeSinceLastFired() const
{
	check(GetWorld());

	const float TimeSinceLastFired = GetWorld()->TimeSince(TimeLastFired);
	return TimeSinceLastFired;
}

bool UFireComponentBase::TryFire(const FVector& Start, const FVector& End)
{
	const bool bCanFire = CanFire();
	if (bCanFire)
	{
		Fire(Start,End);
		UpdateFiringTime();
	}

	return bCanFire;
}

void UFireComponentBase::UpdateFiringTime()
{
	const UWorld* World = GetWorld();
	check(World);
	TimeLastFired = World->GetTimeSeconds();
}
