// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/VerticalProgressBar.h"

#include "DroneGameLogs.h"
#include "Components/Image.h"

void UVerticalProgressBar::SetMaterialColor(const FLinearColor& NewColor)
{
	if (!DynamicMaterialInstance)
	{
		DEBUG_ERROR_LOG("Dynamic material instance is null")
		return;
	}
	DynamicMaterialInstance->SetVectorParameterValue(MaterialColorParamName,NewColor);
}

const FLinearColor& UVerticalProgressBar::GetColor() const
{
	return CurrentColor;
}

void UVerticalProgressBar::SetColor(const FLinearColor& NewLinearColor)
{
	CurrentColor = NewLinearColor;
}

void UVerticalProgressBar::SetMaterialParams()
{
	if (!ProgressBarImage)
	{
		DEBUG_ERROR_LOG("Progress bar image have to be set");
		return;
	}
	if (!ProgressBarMaterial)
	{
		DEBUG_ERROR_LOG("Progress bar material have to be set");
		return;
	}
	
	if (!DynamicMaterialInstance)
	{
		DynamicMaterialInstance = UMaterialInstanceDynamic::Create(ProgressBarMaterial, this);
	}
	SetMaterialPercentage(Percentage);
	SetMaterialColor(CurrentColor);
	
	ProgressBarImage->SetBrushFromMaterial(DynamicMaterialInstance);
}

void UVerticalProgressBar::SetMaterialPercentage(float NewPercentage)
{
	if (!DynamicMaterialInstance)
	{
		DEBUG_ERROR_LOG("Dynamic material instance is null")
		return;
	}

	NewPercentage = FMath::Clamp(NewPercentage,0.f,1.f);
	DynamicMaterialInstance->SetScalarParameterValue(MaterialPercentageParamName,NewPercentage);
}

float UVerticalProgressBar::GetPercentage() const
{
	return Percentage;
}

void UVerticalProgressBar::SetPercentage(float NewPercentage)
{
	Percentage = FMath::Clamp(NewPercentage,0.f,1.f);
}

void UVerticalProgressBar::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetMaterialParams();
}

void UVerticalProgressBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	SetMaterialParams();
}
