// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DroneGamePlayerController.h"
#include "DroneGameLogs.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ADroneGamePlayerController::StartDeath()
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	if (TimerManager.IsTimerActive(DeathTimerHandle))
	{
		DEBUG_LOG("Can not start death, deathTimer is active");
		return;
	}

	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->RemoveFromParent();
	}

	if (DeathWidgetClass)
	{
		DeathWidget = CreateWidget<UUserWidget>(this,DeathWidgetClass);
		DeathWidget->AddToViewport();
	}
	
	APawn* DeadPawn = GetPawn();

	if (OnPawnDeathStartedDelegate.IsBound())
	{
		OnPawnDeathStartedDelegate.Broadcast(DeadPawn,this);
	}
	TimerManager.SetTimer(DeathTimerHandle,this,&ThisClass::OnDeathTimerFinished,DeathTimerTime);
}

bool ADroneGamePlayerController::CanRespawnPlayer() const
{
	return !GetWorld()->GetTimerManager().IsTimerActive(DeathTimerHandle);
}

float ADroneGamePlayerController::GetDeathTimerRemaining() const
{
	return GetWorld()->GetTimerManager().GetTimerRemaining(DeathTimerHandle);
}

bool ADroneGamePlayerController::IsDeathTimerActive() const
{
	return GetWorld()->GetTimerManager().IsTimerActive(DeathTimerHandle);
}

void ADroneGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerHUDWidgetClass)
	{
		PlayerHUDWidget = CreateWidget<UUserWidget>(this,PlayerHUDWidgetClass);
		PlayerHUDWidget->AddToViewport();
	}

}

void ADroneGamePlayerController::OnDeathTimerFinished()
{
	GetWorld()->GetTimerManager().ClearTimer(DeathTimerHandle);

	if (bShouldAutoRestartLevel)
	{
		const bool bRespawnResult = ReloadLevel();
		if (!bRespawnResult)
		{
			DEBUG_LOG("Can not auto respawn player");
		}
	}
	if (OnRespawnTimerFinishedDelegate.IsBound())
	{
		OnRespawnTimerFinishedDelegate.Broadcast(this);
	}
}

bool ADroneGamePlayerController::ReloadLevel()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(DeathTimerHandle))
	{
		return false;
	}
	
	if (DeathWidget)
	{
		DeathWidget->RemoveFromParent();
	}
	UGameplayStatics::OpenLevel(this,FName(UGameplayStatics::GetCurrentLevelName(this)));
	
	return true;
}
