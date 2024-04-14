// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/DronePlayerCameraManager.h"

#include "DroneGameLogs.h"
#include "GameFramework/SpringArmComponent.h"

void ADronePlayerCameraManager::ChangeViewMode(TEnumAsByte<EPlayerViewMode> PlayerViewMode)
{
	const APlayerController* PlayerController = GetOwningPlayerController();
	if (!PlayerController)
	{
		return;
	}

	const APawn* Pawn = PlayerController->GetPawn();
	if (!Pawn)
	{
		return;
	}

	USpringArmComponent* SpringArmComp = Pawn->FindComponentByClass<USpringArmComponent>();
	if (!SpringArmComp)
	{
		return;
	}

	
	if (!ViewMods.Contains(PlayerViewMode))
	{
		DEBUG_LOG("%s does not configured in ViewMods",*UEnum::GetValueAsString(PlayerViewMode))
		return;
	}
	
	const FViewModeSpringArmParams& ViewModeSpringArmParams = ViewMods[PlayerViewMode];
	SpringArmComp->SetRelativeLocation(ViewModeSpringArmParams.TargetLocation);
	SpringArmComp->TargetArmLength = ViewModeSpringArmParams.TargetArmLength;

	CurrentViewMode = PlayerViewMode;
}
