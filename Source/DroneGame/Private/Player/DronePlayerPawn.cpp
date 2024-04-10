// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/DronePlayerPawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Input/BindInputComponent.h"

ADronePlayerPawn::ADronePlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SprintArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	BindInputComponent = CreateDefaultSubobject<UBindInputComponent>("BindInputComponent");
}

void ADronePlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	
	if (BindInputComponent)
	{
		BindInputComponent->SetupPlayerInput(PlayerInputComponent);
	}
}