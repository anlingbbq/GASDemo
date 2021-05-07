// Fill out your copyright notice in the Description page of Project Settings.


#include "GDGameplayAbility.h"

UGDGameplayAbility::UGDGameplayAbility()
{
}

void UGDGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	BeginPlay();
}
