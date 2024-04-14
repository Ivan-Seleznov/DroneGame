// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableItem.h"
#include "GameFramework/Actor.h"
#include "InteractableItemBase.generated.h"

class USphereComponent;

UCLASS()
class DRONEGAME_API AInteractableItemBase : public AActor, public IInteractableItem
{
	GENERATED_BODY()

public:
	AInteractableItemBase();

	virtual void Interact(APawn* InteractingPawn) override;

protected:
	virtual void DestroyItem();

	virtual void SpawnDestroyParticles();
	virtual void PlayInteractSound();
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<USphereComponent> SphereCollision;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UParticleSystem> DestroyParticles;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<USoundBase> InteractSound;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FName DisplayName;
};


