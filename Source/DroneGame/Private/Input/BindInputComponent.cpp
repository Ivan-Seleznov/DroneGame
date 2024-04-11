// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/BindInputComponent.h"
#include "DroneGameLogs.h"
#include "EnhancedInputSubsystems.h"
#include "Movement/DroneMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "Camera/DronePlayerCameraManager.h"
#include "Pawns/DronePawnBase.h"

UBindInputComponent::UBindInputComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UBindInputComponent::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	const APawn* OwningPawn = GetPawn<APawn>();
	if (!OwningPawn)
	{
		return;
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EnhancedInputComponent)
	{
		return;
	}
	
	const APlayerController* PlayerController = Cast<APlayerController>(OwningPawn->GetController());
	check(PlayerController);

	const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	check(LocalPlayer);

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!InputSubsystem)
	{
		return;
	}

	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(DefaultMappingContext,0);

	EnhancedInputComponent->BindAction(MoveInputAction,ETriggerEvent::Triggered,this,&ThisClass::Input_Move);
	EnhancedInputComponent->BindAction(LookInputAction,ETriggerEvent::Triggered,this,&ThisClass::Input_Look);
	EnhancedInputComponent->BindAction(ThrottleInputAction,ETriggerEvent::Triggered,this,&ThisClass::Input_Throttle);
	EnhancedInputComponent->BindAction(ChangeViewModeInputAction,ETriggerEvent::Triggered,this,&ThisClass::Input_ChangeViewMode);
}

void UBindInputComponent::Input_Move(const FInputActionValue& Value)
{
	const ADronePawnBase* Pawn = GetPawn<ADronePawnBase>();
	if (!Pawn)
	{
		return;
	}

	UDroneMovementComponent* DroneMovementComp = Pawn->GetDroneMovementComponent();
	if (!DroneMovementComp)
	{
		return;
	}
	
	const FVector MovementVector = Value.Get<FVector>();
	DroneMovementComp->AddDroneMovementInput(MovementVector);
}

void UBindInputComponent::Input_Look(const FInputActionValue& Value)
{
	const ADronePawnBase* Pawn = GetPawn<ADronePawnBase>();
	if (!Pawn)
	{
		return;
	}
	
	UDroneMovementComponent* DroneMovementComp = Pawn->GetDroneMovementComponent();
	if (!DroneMovementComp)
	{
		return;
	}
	
	const FVector LookVector = Value.Get<FVector>();
	DroneMovementComp->AddDroneMovementInput(LookVector);
}

void UBindInputComponent::Input_Throttle(const FInputActionValue& Value)
{
	const ADronePawnBase* Pawn = GetPawn<ADronePawnBase>();
	if (!Pawn)
	{
		return;
	}
	
	const float Throttle = Value.Get<float>();
	UDroneMovementComponent* DroneMovementComp = Pawn->GetDroneMovementComponent();
	if (!DroneMovementComp)
	{
		return;
	}

	DroneMovementComp->AddDroneThrottle(Throttle);
}

void UBindInputComponent::Input_ChangeViewMode(const FInputActionValue& Value)
{
	const APlayerController* PlayerController = GetController<APlayerController>();
	if (!PlayerController)
	{
		return;
	}

	ADronePlayerCameraManager* DronePlayerCameraManager = Cast<ADronePlayerCameraManager>(PlayerController->PlayerCameraManager);
	if (!DronePlayerCameraManager)
	{
		DEBUG_LOG("Input_ChangeViewMode requires ADronePlayerCameraManager");
		return;
	}

	if (DronePlayerCameraManager->GetCurrentViewMode() == EPlayerViewMode::FirstPerson)
	{
		DronePlayerCameraManager->ChangeViewMode(EPlayerViewMode::ThirdPerson);
	}
	else
	{
		DronePlayerCameraManager->ChangeViewMode(EPlayerViewMode::FirstPerson);
	}
}
