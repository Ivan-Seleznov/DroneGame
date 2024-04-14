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
	UFUNCTION(BlueprintCallable)
	UHealthComponent* GetHealthComponent() const {return HealthComponent;}
	
	void ReceiveDamage(float DamageToReceive,AActor* DamageCauser);
	void ReceiveMaxDamage(AActor* DamageCauser = nullptr);
protected:
	UPROPERTY()
	UHealthComponent* HealthComponent;

	UPROPERTY()
	AActor* LastKnownDamageCauser;
};
