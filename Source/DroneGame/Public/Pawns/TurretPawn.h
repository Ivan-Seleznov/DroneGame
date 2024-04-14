// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamagablePawn.h"
#include "GameFramework/Pawn.h"
#include "TurretPawn.generated.h"

class UHealthComponent;
class UCapsuleComponent;
class UProjectileFireComponent;
class USphereComponent;

UCLASS()
class DRONEGAME_API ATurretPawn : public APawn, public IDamageablePawn
{
	GENERATED_BODY()

public:
	ATurretPawn();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	bool IsPawnVisible() const;

	virtual void OnConstruction(const FTransform& Transform) override;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnPawnDetectionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOutOfHealth(float OldHealth, APawn* OwningPawn);
	
	UFUNCTION(BlueprintPure)
	bool IsPawnLost() const;

	UFUNCTION(BlueprintCallable)
	virtual void ReceiveDamage(float DamageToReceive,AActor* DamageCauser) override;
	UFUNCTION(BlueprintPure)
	virtual UDamageComponent* GetDamageComponent() const override;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> TurretCapsuleCollision;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> MainTurretPartMesh;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> FiringPartMesh;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<USceneComponent> ProjectileSpawnScene;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<USphereComponent> PawnDetectionSphere;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UProjectileFireComponent> ProjectileFireComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UDamageComponent> DamageComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="PawnDetection")
	float PawnDetectionRadius = 5000.f;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="PawnDetection")
	float PawnLossRadius = 6000.f; //pawn loss radius (when the pawn is visible). Should be grater than PawnDetectionRadius
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="PawnDetection")
	float DetectionTimerTime = 2.f;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float TurretRotationSpeed = 50.f;
	
	UPROPERTY(BlueprintReadOnly)
	APawn* CurrentPawn;

	void CleanCurrentPawn();
private:
	void OnPawnDetectionTimerEnd();
	
	UPROPERTY()
	FTimerHandle DetectionTimerHandle;

	bool bIsPawnVisible = false;
};
