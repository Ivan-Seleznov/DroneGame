// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnOutOfHealthDelegate, float, OldHealth, APawn*, OwningPawn);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DRONEGAME_API UHealthComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	UHealthComponent(const FObjectInitializer& ObjectInitializer);

	mutable FOnOutOfHealthDelegate OnOutOfHealthDelegate;
	
	void AddHealth(float HealthToAdd);
	void ReduceHealth(float HealthToReduce);
	
	float GetCurrentHealth() const {return CurrentHealth;}
	float GetMaxHealth() const {return MaxHealth;}

	UFUNCTION(BlueprintPure)
	float GetHealthPercentage() const;
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float DefaultHealth = 100.f;
private:
	void SetHealth(float NewHealth);
	
	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess))
	float CurrentHealth;
};
