// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/InteractableItemBase.h"
#include "DroneGameLogs.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AInteractableItemBase::AInteractableItemBase()
{

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	RootComponent = SphereCollision;
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh");
	ItemMesh->SetupAttachment(SphereCollision);

	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AInteractableItemBase::Interact(APawn* InteractingPawn)
{
	DEBUG_LOG("Interacting with: %s",*DisplayName.ToString());
	PlayInteractSound();
}

void AInteractableItemBase::DestroyItem()
{
	SpawnDestroyParticles();
	Destroy();
}

void AInteractableItemBase::SpawnDestroyParticles()
{
	if (DestroyParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),DestroyParticles,GetActorLocation(),GetActorRotation());
	}	
}
void AInteractableItemBase::PlayInteractSound()
{
	if (InteractSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),InteractSound,GetActorLocation(),GetActorRotation());
	}
}

