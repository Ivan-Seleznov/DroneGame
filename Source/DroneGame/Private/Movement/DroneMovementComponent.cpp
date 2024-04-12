// Fill out your copyright notice in the Description page of Project Settings.

#include "Movement/DroneMovementComponent.h"

#include "DroneGameLogs.h"
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

void UDroneMovementComponent::SetComponentToMove(UPrimitiveComponent* InComp)
{
	if (!InComp->IsSimulatingPhysics())
	{
		DEBUG_LOG("ComponentToMove should simulate physics");
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
	if (!ComponentToMove)
	{
		return 0.f;
	}
	
	const float MaxValue = MaxThrottle * ComponentToMove->GetMass();
	
	const float Range = MaxValue - MinThrottle;
	if (Range == 0.f)
	{
		return 0.f;	
	}
	
	return (CurrentThrottle - MinThrottle) / Range;
}

float UDroneMovementComponent::GetVelocityLength() const
{
	return ComponentToMove ? ComponentToMove->GetComponentVelocity().Length() : 0.f;
}

FVector UDroneMovementComponent::GetVelocity() const
{
	return ComponentToMove ? ComponentToMove->GetComponentVelocity() : FVector(0.f,0.f,0.f);
}

bool UDroneMovementComponent::IsVelocityDown() const
{
	return ComponentToMove ? (ComponentToMove->GetComponentVelocity() | FVector::DownVector) < 0.f : false;
}

void UDroneMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	const APawn* OwningPawn = GetPawn<APawn>();
	check(OwningPawn);
	
	UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(OwningPawn->GetRootComponent());
	if (RootComp)
	{
		SetComponentToMove(RootComp);
	}
	else
	{
		DEBUG_LOG("UPrimitiveComponent is null");
	}
	
	UPhysicsThrusterComponent* ThrusterComp = OwningPawn->FindComponentByClass<UPhysicsThrusterComponent>();
	if (ThrusterComp)
	{
		SetThrusterComponent(ThrusterComp);
	}
	else
	{
		DEBUG_LOG("UPhysicsThrusterComponent is null");
	}

	
}

void UDroneMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!ThrusterComponent || !ComponentToMove)
	{
		DEBUG_LOG("UDroneMovementComponent requires ThrusterComponent and ComponentToMove");
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

