// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AmmoCounterWidget.h"

#include "Components/TextBlock.h"
#include "FireSystem/FireComponentBase.h"

class UFireComponentBase;

void UAmmoCounterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	const APawn* Pawn = GetOwningPlayerPawn();
	if (!Pawn)
	{
		return;
	}

	const UFireComponentBase* FireComponent = Pawn->FindComponentByClass<UFireComponentBase>();
	if (!FireComponent)
	{
		return;
	}
	
	check(CurrentAmmoTextBlock);
	CurrentAmmoTextBlock->SetText(FText::FromString(FString::FromInt(FireComponent->GetCurrentAmmoCount())));
	
	FireComponent->OnAmmoCountChangedDelegate.AddDynamic(this,&ThisClass::OnAmmoCountChanged);
}

void UAmmoCounterWidget::OnAmmoCountChanged(int32 PrevAmmoCount, int32 CurrentAmmoCount)
{
	check(CurrentAmmoTextBlock);

	CurrentAmmoTextBlock->SetText(FText::FromString(FString::FromInt(CurrentAmmoCount)));
}
