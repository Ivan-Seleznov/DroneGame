// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageComponent.h"
#include "DroneDamageComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DRONEGAME_API UDroneDamageComponent : public UDamageComponent
{
	GENERATED_BODY()

public:
	UDroneDamageComponent(const FObjectInitializer& ObjectInitializer);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDroneHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UCurveFloat> DroneHitDamageSpeedCurve;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float MaxFlippedOverTime = 3.f;	// time after that pawn will receive max damage, < 0 = disable
	
	FVector PrevDroneLoc;
	float FlippedOverTimeElapsed;
};
