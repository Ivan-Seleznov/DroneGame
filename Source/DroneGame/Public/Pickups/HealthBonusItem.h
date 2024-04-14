// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableItemBase.h"
#include "HealthBonusItem.generated.h"

UCLASS()
class DRONEGAME_API AHealthBonusItem : public AInteractableItemBase
{
	GENERATED_BODY()

public:
	virtual void Interact(APawn* InteractingPawn) override;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float HealthToAdd = 50.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bAlwaysDestroy = false;
};
