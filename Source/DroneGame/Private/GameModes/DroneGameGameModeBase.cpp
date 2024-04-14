// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameModes/DroneGameGameModeBase.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

void ADroneGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(),APlayerStart::StaticClass(),PlayerStarts);
}

APawn* ADroneGameGameModeBase::RespawnPawn()
{
	FVector PlayerSpawnLocation = FVector::ZeroVector;
	FRotator PlayerSpawnRotation = FRotator::ZeroRotator;

	const int32 PlayerStartIndex = FMath::RandRange(0,PlayerStarts.Num() -1);
	if (!PlayerStarts.IsEmpty() && PlayerStarts.IsValidIndex(PlayerStartIndex))
	{
		const AActor* PlayerStart = PlayerStarts[PlayerStartIndex];
		PlayerSpawnLocation = PlayerStart->GetActorLocation();
		PlayerSpawnRotation = PlayerStart->GetActorForwardVector().Rotation();
	}
	
	APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, PlayerSpawnLocation, PlayerSpawnRotation);
	return SpawnedPawn;
}
