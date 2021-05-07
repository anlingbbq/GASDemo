// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "GDMMCalculation.generated.h"

/**
 * 
 */
UCLASS()
class GASDEMO_API UGDMMCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetCapturedAttributeMagnitude"))
		bool K2_GetCapturedAttributeMagnitude(const FGameplayEffectSpec& Spec, const FGameplayEffectAttributeCaptureDefinition& AttributeDefinition, float& Attribute) const;
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetSetByCallerMagnitude"))
		float K2_GetSetByCallerMagnitude(const FGameplayEffectSpec& Spec, FGameplayTag DataTag, bool WarnIfNotFound = true, float DefaultIfNotFound = 0.f) const;
};
