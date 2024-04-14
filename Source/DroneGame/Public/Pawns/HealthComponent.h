// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnOutOfHealthDelegate, float, OldHealth, APawn*, OwningPawn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealthChangedDelegate,float,OldHealth,float,NewHealth,UHealthComponent*,HealthComponent);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DRONEGAME_API UHealthComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	UHealthComponent(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable)
	mutable FOnOutOfHealthDelegate OnOutOfHealthDelegate;
	UPROPERTY(BlueprintAssignable)
	mutable FOnHealthChangedDelegate OnHealthChangedDelegate;
	
	void AddHealth(float HealthToAdd);
	void ReduceHealth(float HealthToReduce);
	
	float GetCurrentHealth() const {return CurrentHealth;}
	float GetMaxHealth() const {return MaxHealth;}

	UFUNCTION(BlueprintPure)
	float GetHealthPercentage() const;

	bool IsOutOfHealth() const {return bIsOutOfHealth;}

	bool GetEnableHealth() const {return bEnableHealth;}
	void SetEnableHealth(bool bNewEnableHealth) {bEnableHealth = bNewEnableHealth;}
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float DefaultHealth = 100.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	bool bEnableHealth = true;
private:
	void SetHealth(float NewHealth);
	
	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess))
	float CurrentHealth;

	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess))
	bool bIsOutOfHealth = false;
};
