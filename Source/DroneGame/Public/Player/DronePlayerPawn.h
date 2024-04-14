// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/DamagablePawn.h"
#include "Pawns/DronePawnBase.h"
#include "DronePlayerPawn.generated.h"

class UProjectileFireComponent;
class UDroneDamageComponent;
class UHealthComponent;
class UCameraComponent;
class USpringArmComponent;
class UBindInputComponent;


UCLASS()
class DRONEGAME_API ADronePlayerPawn : public ADronePawnBase, public IDamageablePawn
{
	GENERATED_BODY()

public:
	ADronePlayerPawn();
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void Fire();
	
	UFUNCTION(BlueprintCallable)
	virtual void ReceiveDamage(float DamageToReceive,AActor* DamageCauser) override;
	UFUNCTION(BlueprintCallable)
	virtual UDamageComponent* GetDamageComponent() const override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const {return bIsDead;}
	
	virtual void OnDeathFinished();
protected:
	virtual void BeginPlay() override;

	virtual void StartDeath();
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UBindInputComponent> BindInputComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UHealthComponent> HealthComponent;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UDroneDamageComponent> DamageComponent;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UProjectileFireComponent> ProjectileFireComponent;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<USceneComponent> ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float DeathTimerTime = 5.f;
private:
	UFUNCTION()
	void OnOutOfHealth(float OldHealth, APawn* OwningPawn);

	bool bIsDead = false;
};