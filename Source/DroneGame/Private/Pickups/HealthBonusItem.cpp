// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/HealthBonusItem.h"
#include "Pawns/HealthComponent.h"


void AHealthBonusItem::Interact(APawn* InteractingPawn)
{
	Super::Interact(InteractingPawn);

	if (!InteractingPawn)
	{
		return;
	}

	UHealthComponent* PawnHealthComponent = InteractingPawn->FindComponentByClass<UHealthComponent>();
	if (!PawnHealthComponent)
	{
		return;
	}

	PawnHealthComponent->AddHealth(HealthToAdd);

	if (bAlwaysDestroy || !FMath::IsNearlyEqual(PawnHealthComponent->GetCurrentHealth(), PawnHealthComponent->GetMaxHealth()))
	{
		DestroyItem();
	}
}
