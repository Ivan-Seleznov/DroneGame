// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/InteractComponent.h"

#include "DroneGameLogs.h"
#include "..\..\Public\Pickups\InteractableItem.h"


UInteractComponent::UInteractComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

bool UInteractComponent::CanInteract() const
{
	return bCanInteract;
}

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!CollisionDetectionComponent)
	{
		DEBUG_LOG("Collision detection component is not set, try to use root component as collision detection component");
		CollisionDetectionComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	}
	
	if (!CollisionDetectionComponent)
	{
		DEBUG_ERROR_LOG("UInteractComponent requires CollisionDetectionComponent")
		return;
	}

	CollisionDetectionComponent->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::OnComponentBeginOverlap);
}

void UInteractComponent::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OnTryInteract(OtherActor);
	}
}

void UInteractComponent::OnTryInteract(AActor* ActorToInteract)
{
	if (!CanInteract())
	{
		return;
	}
	
	IInteractableItem* InteractableItem = Cast<IInteractableItem>(ActorToInteract);
	if (!InteractableItem)
	{
		return;
	}

	InteractableItem->Interact(GetPawn<APawn>());
}
