﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/DronePlayerPawn.h"

#include "DroneGameLogs.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "FireSystem/ProjectileBase.h"
#include "FireSystem/ProjectileFireComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameModes/DroneGameGameModeBase.h"
#include "Input/BindInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Movement/DroneMovementComponent.h"
#include "Pawns/DroneDamageComponent.h"
#include "Pawns/HealthComponent.h"
#include "Pawns/InteractComponent.h"
#include "Player/DroneGamePlayerController.h"

ADronePlayerPawn::ADronePlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("ProjectileSpawnPoint");
	ProjectileSpawnPoint->SetupAttachment(SkeletalMesh);
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SprintArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	BindInputComponent = CreateDefaultSubobject<UBindInputComponent>("BindInputComponent");
	
	DamageComponent = CreateDefaultSubobject<UDroneDamageComponent>("DamageComponent");
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

	ProjectileFireComponent = CreateDefaultSubobject<UProjectileFireComponent>("ProjectileFireComponent");

	InteractComponent = CreateDefaultSubobject<UInteractComponent>("InteractComponent");
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

void ADronePlayerPawn::Fire()
{
	check(RootComponent);
	check(CameraComponent);
	
	if (!ProjectileFireComponent->GetProjectileClass())
	{
		DEBUG_ERROR_LOG("Projectile class has to be set")
		return;
	}

	ProjectileFireComponent->TryFire(ProjectileSpawnPoint->GetComponentLocation(),CameraComponent->GetForwardVector());
}

void ADronePlayerPawn::ReceiveDamage(float DamageToReceive,AActor* DamageCauser)
{
	if (DamageComponent)
	{
		DamageComponent->ReceiveDamage(DamageToReceive,DamageCauser);	
	}
}

UDamageComponent* ADronePlayerPawn::GetDamageComponent() const
{
	return DamageComponent;
}

void ADronePlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	check(DamageComponent);
	DamageComponent->SetHealthComponent(HealthComponent);

	check(HealthComponent);
	HealthComponent->OnOutOfHealthDelegate.AddDynamic(this,&ThisClass::OnOutOfHealth);
}

void ADronePlayerPawn::StartDeath()
{
	if (bIsDead)
	{
		return;
	}
	
	ADroneGamePlayerController* DroneGamePlayerController = Cast<ADroneGamePlayerController>(GetController());
	if (!DroneGamePlayerController)
	{
		return;
	}
	
	check(DroneMovementComponent);
	DroneMovementComponent->DisableAllMovement();

	check(ProjectileFireComponent);
	ProjectileFireComponent->DisableFire();

	check(InteractComponent);
	InteractComponent->SetCanInteract(false);
	
	bIsDead = true;
	DroneGamePlayerController->StartDeath();
}

void ADronePlayerPawn::OnOutOfHealth(float OldHealth, APawn* OwningPawn)
{
	StartDeath();
}



/*Debug Commands*/
void ADronePlayerPawn::KillYourself()
{
	StartDeath();
}

void ADronePlayerPawn::AddHealth(float HealthToAdd)
{
	if (HealthComponent)
	{
		HealthComponent->AddHealth(HealthToAdd);
	}
}

void ADronePlayerPawn::DisableHealth()
{
	if (HealthComponent)
	{
		HealthComponent->SetEnableHealth(false);
	}
}

void ADronePlayerPawn::EnableHealth()
{
	if (HealthComponent)
	{
		HealthComponent->SetEnableHealth(true);
	}
}

void ADronePlayerPawn::DisableAmmoCount()
{
	if (ProjectileFireComponent)
	{
		ProjectileFireComponent->SetShouldUseAmmo(false);
	}
}

void ADronePlayerPawn::EnableAmmoCount()
{
	if (ProjectileFireComponent)
	{
		ProjectileFireComponent->SetShouldUseAmmo(true);
	}
}
