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

	const bool bHadMaxHealth = FMath::IsNearlyEqual(PawnHealthComponent->GetCurrentHealth(), PawnHealthComponent->GetMaxHealth());
	PawnHealthComponent->AddHealth(HealthToAdd);

	if (bAlwaysDestroy || !bHadMaxHealth)
	{
		DestroyItem();
	}
}
