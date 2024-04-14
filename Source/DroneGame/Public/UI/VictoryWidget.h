// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DroneGameWidgetBase.h"
#include "VictoryWidget.generated.h"


class UButton;

UCLASS()
class DRONEGAME_API UVictoryWidget : public UDroneGameWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnRestartLevelButtonClicked();
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> RestartLevelButton;
};
