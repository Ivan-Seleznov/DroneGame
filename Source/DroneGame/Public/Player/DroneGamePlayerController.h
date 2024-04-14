// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DroneGamePlayerController.generated.h"

class ADroneGamePlayerController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRespawnTimerFinishedDelegate,ADroneGamePlayerController*, PlayerController);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPawnDeathStartedDelegate,APawn*, DeadPawn,ADroneGamePlayerController*, PlayerController);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDeathFinishedDelegate,APawn*, RespawnedPawn,ADroneGamePlayerController*, PlayerController);

/**
 * DroneGame PlayerController class
 */
UCLASS()
class DRONEGAME_API ADroneGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	mutable FOnRespawnTimerFinishedDelegate OnRespawnTimerFinishedDelegate;
	mutable FOnPawnDeathStartedDelegate OnPawnDeathStartedDelegate;
	mutable FOnDeathFinishedDelegate OnPawnDeathFinished;
	
	void StartDeath();

	float GetDeathTimerTime() const {return DeathTimerTime;}
	void SetDeathTimerTime(float NewDeathTimerTime) {DeathTimerTime = NewDeathTimerTime;}

	bool GetShouldAutoRestartLevel() const {return bShouldAutoRestartLevel;}
	void SetShouldAutoRestartLevel(bool bNewShouldAutoRespawnPawn) {bShouldAutoRestartLevel = bNewShouldAutoRespawnPawn;}
	
	UFUNCTION(BlueprintPure)
	bool CanRespawnPlayer() const;

	UFUNCTION(BlueprintPure)
	float GetDeathTimerRemaining() const;
	UFUNCTION(BlueprintPure)
	bool IsDeathTimerActive() const;
protected:
	virtual void BeginPlay() override;
	void OnDeathTimerFinished();

	bool ReloadLevel();
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float DeathTimerTime = 5.f;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	bool bShouldAutoRestartLevel = true;

private:
	UPROPERTY()
	FTimerHandle DeathTimerHandle;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess))
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
	UPROPERTY()
	UUserWidget* PlayerHUDWidget;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess))
	TSubclassOf<UUserWidget> DeathWidgetClass;
	UPROPERTY()
	UUserWidget* DeathWidget;
};
