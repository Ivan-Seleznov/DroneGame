// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawns/TurretPawn.h"
#include "DroneGameLogs.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "FireSystem/ProjectileFireComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pawns/DamageComponent.h"
#include "Pawns/HealthComponent.h"

ATurretPawn::ATurretPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	TurretCapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>("TurretCapsuleCollisionComponent");
	RootComponent = TurretCapsuleCollision;

	PawnDetectionSphere = CreateDefaultSubobject<USphereComponent>("PawnDetectionSphere");
	PawnDetectionSphere->SetupAttachment(RootComponent);

	MainTurretPartMesh = CreateDefaultSubobject<UStaticMeshComponent>("MainTurretPartMesh");
	MainTurretPartMesh->SetupAttachment(RootComponent);
	MainTurretPartMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	FiringPartMesh = CreateDefaultSubobject<UStaticMeshComponent>("FiringPartMesh");
	FiringPartMesh->SetupAttachment(MainTurretPartMesh);
	FiringPartMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileSpawnScene = CreateDefaultSubobject<USceneComponent>("ProjectileSpawnScene");
	ProjectileSpawnScene->SetupAttachment(FiringPartMesh);
	
	PawnDetectionSphere->SetSphereRadius(PawnDetectionRadius);
	
	ProjectileFireComponent = CreateDefaultSubobject<UProjectileFireComponent>("ProjectileFireComponent");

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	DamageComponent = CreateDefaultSubobject<UDamageComponent>("DamageComponent");
}

void ATurretPawn::BeginPlay()
{
	Super::BeginPlay();

	check(DamageComponent);
	DamageComponent->SetHealthComponent(HealthComponent);
	
	check(PawnDetectionSphere)
	PawnDetectionSphere->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::OnPawnDetectionSphereBeginOverlap);

	check(HealthComponent)
	HealthComponent->OnOutOfHealthDelegate.AddDynamic(this,&ThisClass::OnOutOfHealth);
}

void ATurretPawn::OnPawnDetectionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this)
	{
		return;
	}
	
	APawn* Pawn = Cast<APawn>(OtherActor);
	if(!Pawn)
	{
		return;
	}
	
	if (!IsPawnVisible())
	{
		CurrentPawn = Pawn;
		GetWorld()->GetTimerManager().SetTimer(DetectionTimerHandle,this,&ThisClass::OnPawnDetectionTimerEnd,DetectionTimerTime,false);
	}
}

void ATurretPawn::OnOutOfHealth(float OldHealth, APawn* OwningPawn)
{
	//TODO visual effects, sound, player state
	
	Destroy();
}

bool ATurretPawn::IsPawnLost() const
{
	bool bIsPawnDead = false;
	if (const IDamageablePawn* DamageablePawn = Cast<IDamageablePawn>(CurrentPawn))
	{
		if (const UDamageComponent* CurrentPawnDamageComponent = DamageablePawn->GetDamageComponent())
		{
			if (const UHealthComponent* CurrentPawnHealthComponent = CurrentPawnDamageComponent->GetHealthComponent())
			{
				bIsPawnDead = CurrentPawnHealthComponent->IsOutOfHealth();
			}
		}
	}
	
	return !CurrentPawn || bIsPawnDead || FVector::Distance(CurrentPawn->GetActorLocation(),PawnDetectionSphere->GetComponentLocation()) > PawnLossRadius;
}

void ATurretPawn::ReceiveDamage(float DamageToReceive,AActor* DamageCauser)
{
	DamageComponent->ReceiveDamage(DamageToReceive,DamageCauser);
}

UDamageComponent* ATurretPawn::GetDamageComponent() const
{
	return DamageComponent;
}

void ATurretPawn::CleanCurrentPawn()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(DetectionTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(DetectionTimerHandle);
	}
	CurrentPawn = nullptr;
	bIsPawnVisible = false;
}

void ATurretPawn::OnPawnDetectionTimerEnd()
{
	if (CurrentPawn)
	{
		bIsPawnVisible = true;
	}
}

void ATurretPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsPawnLost())
	{
		CleanCurrentPawn();
		return;
	}

	const FVector DirectionToPawn = (CurrentPawn->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	const FRotator TargetRotation = DirectionToPawn.Rotation();
	const FRotator NewTurretRotation = UKismetMathLibrary::RInterpTo(FiringPartMesh->GetComponentRotation(),TargetRotation,DeltaTime,TurretRotationSpeed);
	FiringPartMesh->SetWorldRotation(NewTurretRotation);
	
	if (IsPawnVisible())
	{
		ProjectileFireComponent->TryFire(ProjectileSpawnScene->GetComponentLocation(),FiringPartMesh->GetComponentRotation().Vector());
	}
}

bool ATurretPawn::IsPawnVisible() const
{
	return CurrentPawn && bIsPawnVisible;
}

void ATurretPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (PawnDetectionSphere)
	{
		PawnDetectionSphere->SetSphereRadius(PawnDetectionRadius);
	}
}
