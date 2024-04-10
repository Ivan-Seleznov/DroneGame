// Fill out your copyright notice in the Description page of Project Settings.

#include "Movement/DroneMovementComponent.h"

#include "PhysicsEngine/PhysicsThrusterComponent.h"

UDroneMovementComponent::UDroneMovementComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDroneMovementComponent::AddDroneMovementInput(const FVector& Value)
{
	if (Value != FVector::ZeroVector)
	{
		MoveInput = Value;
	}
}

void UDroneMovementComponent::AddDroneThrottle(float Value)
{
	if (Value != 0.f)
	{
		ThrottleInput += Value;
	}
}

void UDroneMovementComponent::InitDroneMovement(UPrimitiveComponent* InMoveComp,
	UPhysicsThrusterComponent* InThrusterComp)
{
	if (!InMoveComp || !InThrusterComp)
	{
		//TODO: add log
		return;
	}

	SetComponentToMove(InMoveComp);
	SetThrusterComponent(InThrusterComp);
}

void UDroneMovementComponent::SetComponentToMove(UPrimitiveComponent* InComp)
{
	if (!InComp->IsSimulatingPhysics())
	{
		//TODO: warning logging 
	}
	ComponentToMove = InComp;
}

void UDroneMovementComponent::SetThrusterComponent(UPhysicsThrusterComponent* InComp)
{
	if (!InComp->IsActive())
	{
		InComp->Activate();
	}
	
	ThrusterComponent = InComp;
}

float UDroneMovementComponent::GetThrottlePercent() const
{
	const float MaxValue = MaxThrottle * ComponentToMove->GetMass();
	
	const float Range = MaxValue - MinThrottle;
	if (Range == 0.f)
	{
		return 0.f;	
	}
	
	return (CurrentThrottle - MinThrottle) / Range;
}

void UDroneMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDroneMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!ThrusterComponent || !ComponentToMove)
	{
		//TODO: add log
		return;
	}
	
	/*Handle throttle*/
	CurrentThrottle += ThrottleInput * ThrottleSpeed * ComponentToMove->GetMass() * DeltaTime;
	CurrentThrottle = FMath::Clamp(CurrentThrottle,MinThrottle,MaxThrottle * ComponentToMove->GetMass());
	
	ThrusterComponent->ThrustStrength = CurrentThrottle;

	/*Handle movement*/
	ComponentToMove->AddTorqueInDegrees(ComponentToMove->GetForwardVector() * (MoveInput.X * RotationSpeed * -1.f),NAME_None,true);
	ComponentToMove->AddTorqueInDegrees(ComponentToMove->GetRightVector() * (MoveInput.Y * RotationSpeed),NAME_None,true);
	ComponentToMove->AddTorqueInDegrees(ComponentToMove->GetUpVector() * (MoveInput.Z * RotationSpeed),NAME_None,true);
	
	ThrottleInput = 0.f;
	MoveInput = FVector::ZeroVector;
}

