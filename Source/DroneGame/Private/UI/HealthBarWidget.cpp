// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthBarWidget.h"

#include "Components/ProgressBar.h"
#include "Pawns/HealthComponent.h"

void UHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	const APawn* Pawn = GetOwningPlayerPawn();
	if (!Pawn)
	{
		return;
	}

	const UHealthComponent* HealthComponent = Pawn->FindComponentByClass<UHealthComponent>();
	if (!HealthComponent)
	{
		return;
	}

	check(ProgressBar);
	ProgressBar->SetPercent(HealthComponent->GetHealthPercentage());
	
	HealthComponent->OnHealthChangedDelegate.AddDynamic(this,&ThisClass::OnPawnHealthChanged);
}

void UHealthBarWidget::OnPawnHealthChanged(float OldHealth, float NewHealth, UHealthComponent* HealthComponent)
{
	if (!HealthComponent || !ProgressBar)
	{
		return;
	}

	ProgressBar->SetPercent(HealthComponent->GetHealthPercentage());
}
