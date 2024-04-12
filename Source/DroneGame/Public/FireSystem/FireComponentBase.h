﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "FireComponentBase.generated.h"

UCLASS(Abstract)
class DRONEGAME_API UFireComponentBase : public UPawnComponent
{
	GENERATED_BODY()

public:
	UFireComponentBase(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure)
	virtual bool CanFire() const;

	bool IsFireRateValid() const;
	
	float GetCurrentFireRate() const;
	float GetTimeSinceLastFired() const;

	UFUNCTION(BlueprintCallable)
	bool TryFire(const FVector& Start, const FVector& End);

	UFUNCTION(BlueprintCallable)
	void SetShouldUseAmmo(bool bNewShouldUseAmo) {bShouldUseAmmo = true;}

	UFUNCTION(BlueprintPure)
	bool GetShouldUseAmmo() const {return bShouldUseAmmo;}
protected:
	virtual void BeginPlay() override;

	virtual void Fire(const FVector& Start, const FVector& End);
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float FireRate = 2.0f;

private:
	void UpdateFiringTime();

	float TimeLastFired;

	UPROPERTY(EditDefaultsOnly,meta=(AllowPrivateAccess))
	bool bShouldUseAmmo = true;
};
 