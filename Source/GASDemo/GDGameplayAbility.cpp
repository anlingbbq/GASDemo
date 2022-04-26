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

bool UGDGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	UNetDriver* NetDriver = ActorInfo->AvatarActor.Get()->GetWorld()->GetNetDriver();
	if (bTestPredcition && NetDriver->IsServer())
	{
		return false;
	}

	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UGDGameplayAbility::TestDebug()
{
	UE_LOG(LogTemp, Log, TEXT(">>>>>>>>>>>> Test"))
}
