// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/DronePlayerPawn.h"

#include "DroneGameLogs.h"
#include "Camera/CameraComponent.h"
#include "FireSystem/ProjectileBase.h"
#include "FireSystem/ProjectileFireComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Input/BindInputComponent.h"
#include "Pawns/DroneDamageComponent.h"
#include "Pawns/HealthComponent.h"

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

void ADronePlayerPawn::ReceiveDamage(float DamageToReceive)
{
	if (DamageComponent)
	{
		DamageComponent->ReceiveDamage(DamageToReceive);	
	}
}

UDamageComponent* ADronePlayerPawn::GetDamageComponent() const
{
	return DamageComponent;
}

void ADronePlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	if (DamageComponent)
	{
		DamageComponent->SetHealthComponent(HealthComponent);
	}
}
