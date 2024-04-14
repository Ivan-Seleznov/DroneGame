// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DroneGameWidgetBase.h"
#include "HealthBarWidget.generated.h"

class UProgressBar;
class UHealthComponent;

/**
 * Health bar widget class
 */
UCLASS()
class DRONEGAME_API UHealthBarWidget : public UDroneGameWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnPawnHealthChanged(float OldHealth,float NewHealth,UHealthComponent* HealthComponent);
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> ProgressBar;
};
