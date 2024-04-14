// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DroneGameWidgetBase.h"
#include "VerticalProgressBar.generated.h"

class UImage;

UCLASS(Abstract)
class DRONEGAME_API UVerticalProgressBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	const FLinearColor& GetColor() const;
	UFUNCTION()
	void SetColor(const FLinearColor& NewLinearColor);
	
	UFUNCTION(BlueprintPure)
	float GetPercentage() const;
	UFUNCTION(BlueprintCallable)
	void SetPercentage(float NewPercentage);
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FName MaterialColorParamName = "Color";
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FName MaterialPercentageParamName = "Percentage";
private:
	void SetMaterialParams();
	
	void SetMaterialPercentage(float NewPercentage);
	void SetMaterialColor(const FLinearColor& NewColor);

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> ProgressBarImage;

	UPROPERTY(EditDefaultsOnly,meta=(AllowPrivateAccess))
	TObjectPtr<UMaterialInstance> ProgressBarMaterial;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterialInstance;

	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess))
	FLinearColor CurrentColor = FLinearColor(255.f,255.f,255.f);

	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess, UIMin=0, ClampMin=0, UIMax=1, ClampMax=1))
	float Percentage = 0.f;
};