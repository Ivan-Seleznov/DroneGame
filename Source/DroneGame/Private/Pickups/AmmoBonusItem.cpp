

#include "Pickups/AmmoBonusItem.h"

#include "FireSystem/FireComponentBase.h"


void AAmmoBonusItem::Interact(APawn* InteractingPawn)
{
	Super::Interact(InteractingPawn);

	if (!InteractingPawn)
	{
		return;
	}

	UFireComponentBase* FireComponentBase = InteractingPawn->FindComponentByClass<UFireComponentBase>();
	if (!FireComponentBase)
	{
		return;
	}

	FireComponentBase->AddAmmo(AmmoToAdd);
	DestroyItem();
}
