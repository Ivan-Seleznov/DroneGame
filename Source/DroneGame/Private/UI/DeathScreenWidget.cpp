// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DeathScreenWidget.h"

#include "Components/TextBlock.h"
#include "Player/DroneGamePlayerController.h"

void UDeathScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UDeathScreenWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	const ADroneGamePlayerController* DroneGamePlayerController = Cast<ADroneGamePlayerController>(GetOwningPlayer());
	if (!DroneGamePlayerController)
	{
		return;
	}

	
	if (DroneGamePlayerController->IsDeathTimerActive())
	{
		DeathTimerTextBlock->SetText(FText::FromString(FString::FromInt(DroneGamePlayerController->GetDeathTimerRemaining())));
	}
}
