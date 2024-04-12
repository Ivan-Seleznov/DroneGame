// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "DamageComponent.generated.h"


class UHealthComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DRONEGAME_API UDamageComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	UDamageComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void SetHealthComponent(UHealthComponent* InHealthComp) {HealthComponent = InHealthComp;}
	
	void ReceiveDamage(float DamageToReceive);
	void ReceiveMaxDamage();
protected:
	UPROPERTY()
	UHealthComponent* HealthComponent;
};
