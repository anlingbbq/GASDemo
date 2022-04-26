// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GDGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GASDEMO_API UGDGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGDGameplayAbility();

	UFUNCTION(BlueprintImplementableEvent)
		void BeginPlay();
	
	void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
	
	UPROPERTY(EditDefaultsOnly)
		bool bTestPredcition = false;
};
