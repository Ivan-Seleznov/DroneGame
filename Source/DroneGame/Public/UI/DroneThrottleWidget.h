// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DroneGameWidgetBase.h"
#include "DroneThrottleWidget.generated.h"


class UVerticalProgressBar;
class UDroneMovementComponent;

UCLASS()
class DRONEGAME_API UDroneThrottleWidget : public UDroneGameWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ThrottlePercentageTextBlock;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalProgressBar> VerticalProgressBar;
	
	UPROPERTY()
	UDroneMovementComponent* DroneMovementComp;
};
