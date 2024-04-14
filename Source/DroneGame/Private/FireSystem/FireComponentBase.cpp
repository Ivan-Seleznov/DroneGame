// Fill out your copyright notice in the Description page of Project Settings.


#include "FireSystem/FireComponentBase.h"
#include "DroneGameLogs.h"

UFireComponentBase::UFireComponentBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UFireComponentBase::Fire(const FVector& StartLocation, const FVector& Direction)
{
}

void UFireComponentBase::AddAmmo(float AmmoToAdd)
{
	SetAmmoCount(CurrentAmmoCount + AmmoToAdd);
}

bool UFireComponentBase::IsEnoughAmmo() const
{
	return !bShouldUseAmmo || CurrentAmmoCount > 0;
}

void UFireComponentBase::BeginPlay()
{
	Super::BeginPlay();

	SetAmmoCount(StartAmmoCount >= 0 ? StartAmmoCount : 0);
}

bool UFireComponentBase::CanFire() const
{
	return IsFireRateValid() && IsEnoughAmmo();
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
		UpdateAmmoCount();
	}

	return bCanFire;
}

void UFireComponentBase::UpdateFiringTime()
{
	const UWorld* World = GetWorld();
	check(World);
	TimeLastFired = World->GetTimeSeconds();
}

void UFireComponentBase::UpdateAmmoCount()
{
	SetAmmoCount(CurrentAmmoCount - 1);
}

void UFireComponentBase::SetAmmoCount(int32 NewAmmoCount)
{
	const int32 PrevAmmoCount = CurrentAmmoCount;
	
	CurrentAmmoCount = NewAmmoCount;
	if (CurrentAmmoCount < 0)
	{
		CurrentAmmoCount = 0;
	}
	
	if (OnAmmoCountChangedDelegate.IsBound())
	{
		OnAmmoCountChangedDelegate.Broadcast(PrevAmmoCount,CurrentAmmoCount);
	}
}
