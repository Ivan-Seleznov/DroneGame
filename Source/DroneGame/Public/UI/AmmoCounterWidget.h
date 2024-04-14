// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DroneGameWidgetBase.h"
#include "AmmoCounterWidget.generated.h"

/**
 * AmmoCounterWidget class
 */
UCLASS()
class DRONEGAME_API UAmmoCounterWidget : public UDroneGameWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void OnAmmoCountChanged(int32 PrevAmmoCount,int32 CurrentAmmoCount);
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> CurrentAmmoTextBlock;
};
