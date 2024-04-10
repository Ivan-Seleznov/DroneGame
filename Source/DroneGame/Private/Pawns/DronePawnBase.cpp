// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawns/DronePawnBase.h"

#include "Components/BoxComponent.h"
#include "Movement/DroneMovementComponent.h"
#include "PhysicsEngine/PhysicsThrusterComponent.h"

ADronePawnBase::ADronePawnBase()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	RootComponent = BoxComponent;

	PhysicsThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>("PhysicsThrusterComponent");
	PhysicsThruster->SetupAttachment(RootComponent);
	
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SkeletalMesh->SetupAttachment(RootComponent);

	DroneMovementComponent = CreateDefaultSubobject<UDroneMovementComponent>("DroneMovementComponent");
}

void ADronePawnBase::BeginPlay()
{
	Super::BeginPlay();

	DroneMovementComponent->InitDroneMovement(BoxComponent,PhysicsThruster);
}

void ADronePawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}