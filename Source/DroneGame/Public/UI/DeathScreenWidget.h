// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DroneGameWidgetBase.h"
#include "DeathScreenWidget.generated.h"

/**
 * Death screen widget class
 */
UCLASS(Abstract)
class DRONEGAME_API UDeathScreenWidget : public UDroneGameWidgetBase
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
private:
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> DeathTimerTextBlock;
};
