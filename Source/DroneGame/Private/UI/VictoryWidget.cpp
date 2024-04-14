// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/VictoryWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UVictoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	check(RestartLevelButton);
	RestartLevelButton->OnClicked.AddDynamic(this,&ThisClass::OnRestartLevelButtonClicked);
}

void UVictoryWidget::OnRestartLevelButtonClicked()
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (!PlayerController)
	{
		return;
	}

	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bShowMouseCursor = false;

	UGameplayStatics::OpenLevel(this,FName(UGameplayStatics::GetCurrentLevelName(this)));
}
