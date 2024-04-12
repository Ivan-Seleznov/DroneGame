// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireComponentBase.h"
#include "ProjectileFireComponent.generated.h"

class AProjectileBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DRONEGAME_API UProjectileFireComponent : public UFireComponentBase
{
	GENERATED_BODY()

public:
	UProjectileFireComponent(const FObjectInitializer& ObjectInitializer);

	TSubclassOf<AProjectileBase> GetProjectileClass() const {return ProjectileClass;}
	void SetProjectileClass(TSubclassOf<AProjectileBase> InProjectileClass) {ProjectileClass = InProjectileClass;}

	virtual bool CanFire() const override;
protected:
	virtual void Fire(const FVector& Start, const FVector& End) override;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess))
	TSubclassOf<AProjectileBase> ProjectileClass;
};
