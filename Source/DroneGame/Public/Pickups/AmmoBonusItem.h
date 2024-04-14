// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableItemBase.h"
#include "AmmoBonusItem.generated.h"

UCLASS()
class DRONEGAME_API AAmmoBonusItem : public AInteractableItemBase
{
	GENERATED_BODY()

public:
	virtual void Interact(APawn* InteractingPawn) override;

	int32 GetAmmoToAdd() const {return AmmoToAdd;}
	void SetAmmoToAdd(int32 NewAmmoToAdd) {AmmoToAdd = NewAmmoToAdd;}
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 AmmoToAdd = 10;
};
