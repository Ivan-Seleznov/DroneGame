// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "FireComponentBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoCountChangedDelegate,int32, PrevAmmoCount, int32, CurrentAmmoCount);

UCLASS(Abstract)
class DRONEGAME_API UFireComponentBase : public UPawnComponent
{
	GENERATED_BODY()

public:
	UFireComponentBase(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable)
	mutable FOnAmmoCountChangedDelegate OnAmmoCountChangedDelegate;
	
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
	
	float GetCurrentAmmoCount() const {return CurrentAmmoCount;}
	UFUNCTION(BlueprintCallable)
	void AddAmmo(float AmmoToAdd);

	bool IsEnoughAmmo() const;
protected:
	virtual void BeginPlay() override;

	virtual void Fire(const FVector& Start, const FVector& End);
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float FireRate = 2.0f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, meta=(EditCondition="bShouldUseAmmo"))
	int32 StartAmmoCount = 100;
private:
	void UpdateFiringTime();
	void UpdateAmmoCount();

	void SetAmmoCount(int32 NewAmmoCount);
	
	float TimeLastFired;

	UPROPERTY(EditDefaultsOnly,meta=(AllowPrivateAccess))
	bool bShouldUseAmmo = true;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	int32 CurrentAmmoCount = 0;
};
 