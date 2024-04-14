// Fill out your copyright notice in the Description page of Project Settings.


#include "FireSystem/ProjectileBase.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/DamagablePawn.h"


AProjectileBase::AProjectileBase()
{
	SphereCollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereCollisionComponent");
	RootComponent = SphereCollisionComponent;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMeshComponent->SetupAttachment(SphereCollisionComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovementComponent->SetUpdatedComponent(SphereCollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 1000;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.7f;
	
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (SphereCollisionComponent)
	{
		SphereCollisionComponent->IgnoreActorWhenMoving(GetOwner(),true);
		SphereCollisionComponent->OnComponentHit.AddDynamic(this,&ThisClass::OnHit);
	}
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherActor != GetOwner())
	{
		if (IDamageablePawn* DamageablePawn = Cast<IDamageablePawn>(OtherActor))
        {
        	DamageablePawn->ReceiveDamage(ProjectileDamage,GetOwner());
        }
	}
	
	if (Hit.IsValidBlockingHit())
	{
		
		if (HitParticles)
		{
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(Hit.Location);
			SpawnTransform.SetScale3D(FVector(1,1,1));
			SpawnTransform.SetRotation(Hit.Location.Rotation().Quaternion());
			
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitParticles,SpawnTransform);
		}
		if (HitSound)
		{
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(),HitSound,GetActorLocation(),GetActorRotation());
		}
	}
	DestroyProjectile();
}

void AProjectileBase::DestroyProjectile()
{
	Destroy();
}

