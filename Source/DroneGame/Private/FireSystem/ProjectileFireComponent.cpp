// Fill out your copyright notice in the Description page of Project Settings.


#include "FireSystem/ProjectileFireComponent.h"
#include "FireSystem/ProjectileBase.h"
#include "DroneGameLogs.h"


UProjectileFireComponent::UProjectileFireComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UProjectileFireComponent::Fire(const FVector& Start, const FVector& End)
{
	Super::Fire(Start, End);
	
	FTransform SpawnTransform = FTransform::Identity;
	SpawnTransform.SetLocation(Start);
	SpawnTransform.SetRotation(End.ToOrientationQuat());
	
	AProjectileBase* Projectile = GetWorld()->SpawnActorDeferred<AProjectileBase>(ProjectileClass,SpawnTransform);
	Projectile->SetOwner(GetOwner());
	
	Projectile->FinishSpawning(SpawnTransform);
}

bool UProjectileFireComponent::CanFire() const
{
	if (!ProjectileClass)
	{
		DEBUG_ERROR_LOG("FireComponent requires Projectile class wich is invalid now")
	}
	
	return Super::CanFire() && ProjectileClass;
}

