// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DroneThrottleWidget.h"

#include "DroneGameLogs.h"
#include "Components/TextBlock.h"
#include "Movement/DroneMovementComponent.h"
#include "UI/VerticalProgressBar.h"

void UDroneThrottleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	const APawn* Pawn = GetOwningPlayerPawn();
	if (!Pawn)
	{
		return;
	}

	DroneMovementComp = Pawn->FindComponentByClass<UDroneMovementComponent>();
	VerticalProgressBar->SetPercentage(0.f);
}

void UDroneThrottleWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!DroneMovementComp)
	{
		DEBUG_ERROR_LOG("DroneThrottleWidget requires DroneMovementComponent");
		return;
	}
	
	const float ThrottlePercent = DroneMovementComp->GetThrottlePercent();
	VerticalProgressBar->SetPercentage(ThrottlePercent);

	ThrottlePercentageTextBlock->SetText(FText::FromString(FString::FromInt(FMath::FloorToInt(ThrottlePercent * 100))));
}
