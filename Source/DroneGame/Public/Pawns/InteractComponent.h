// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "InteractComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DRONEGAME_API UInteractComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	UInteractComponent(const FObjectInitializer& ObjectInitializer);

	void SetCollisionDetectionComponent(UPrimitiveComponent* InComponent) {CollisionDetectionComponent = InComponent;}
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	virtual void OnTryInteract(AActor* ActorToInteract);
private:
	UPROPERTY()
	UPrimitiveComponent* CollisionDetectionComponent;
};
