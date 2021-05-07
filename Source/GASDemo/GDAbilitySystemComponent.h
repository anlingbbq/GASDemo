// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GDAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class GASDEMO_API UGDAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		TArray<UGameplayAbility*> GetAbilityInstances(FGameplayAbilitySpecHandle Handle);
	UFUNCTION(BlueprintCallable)
		UGameplayAbility* GetSingleAbilityInstance(FGameplayAbilitySpecHandle Handle);
};
