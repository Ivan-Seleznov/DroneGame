// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/DroneDamageComponent.h"

#include "DroneGameLogs.h"
#include "Components/BoxComponent.h"
#include "Movement/DroneMovementComponent.h"
#include "Player/DronePlayerPawn.h"

class UDroneMovementComponent;
class ADronePawnBase;

UDroneDamageComponent::UDroneDamageComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDroneDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const ADronePawnBase* DronePawn = GetPawn<ADronePawnBase>();
	if (!DronePawn)
	{
		return;
	}
	
	UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(DronePawn->GetRootComponent());
	if (!PrimitiveComponent)
	{
		return;
	}

	if ((PrimitiveComponent->GetUpVector() | FVector::UpVector) < -0.8f && PrimitiveComponent->GetComponentLocation() == PrevDroneLoc)
	{
		if (MaxFlippedOverTime > 0.f && FlippedOverTimeElapsed >= MaxFlippedOverTime)
		{
			//DEBUG_SLOG("Received Max damage", FColor::Blue);
			ReceiveMaxDamage();
		}
		FlippedOverTimeElapsed += DeltaTime;
	}
	PrevDroneLoc = PrimitiveComponent->GetComponentLocation();
}

void UDroneDamageComponent::BeginPlay()
{
	Super::BeginPlay();
	
	const ADronePlayerPawn* DronePawn = GetPawn<ADronePlayerPawn>();
	if (!DronePawn)
	{
		return;
	}

	UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(DronePawn->GetRootComponent());
	if (!PrimitiveComponent)
	{
		return;
	}

	PrimitiveComponent->OnComponentHit.AddDynamic(this,&ThisClass::OnDroneHit);
	
}

void UDroneDamageComponent::OnDroneHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	const ADronePawnBase* DronePawn = GetPawn<ADronePawnBase>();
	if (!DronePawn)
	{
		return;
	}

	UDroneMovementComponent* DroneMovementComponent = DronePawn->GetDroneMovementComponent();
	if (!DroneMovementComponent)
	{
		return;
	}
	
	if (DroneHitDamageSpeedCurve)
	{
		ReceiveDamage(DroneHitDamageSpeedCurve->GetFloatValue(DroneMovementComponent->GetVelocity().GetSafeNormal() | Hit.Normal),nullptr);
	}
}
