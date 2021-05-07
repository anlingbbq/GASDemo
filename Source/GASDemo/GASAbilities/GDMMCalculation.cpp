// Fill out your copyright notice in the Description page of Project Settings.


#include "GASDemo/GASAbilities/GDMMCalculation.h"

bool UGDMMCalculation::K2_GetCapturedAttributeMagnitude(const FGameplayEffectSpec& Spec,
	const FGameplayEffectAttributeCaptureDefinition& AttributeDefinition, float& Attribute) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	
	return GetCapturedAttributeMagnitude(AttributeDefinition, Spec, EvaluationParameters, Attribute);
}

float UGDMMCalculation::K2_GetSetByCallerMagnitude(const FGameplayEffectSpec& Spec, FGameplayTag DataTag,
	bool WarnIfNotFound, float DefaultIfNotFound) const
{
	return Spec.GetSetByCallerMagnitude(DataTag, WarnIfNotFound, DefaultIfNotFound);
}
