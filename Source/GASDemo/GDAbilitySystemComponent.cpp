// Fill out your copyright notice in the Description page of Project Settings.


#include "GDAbilitySystemComponent.h"

TArray<UGameplayAbility*> UGDAbilitySystemComponent::GetAbilityInstances(FGameplayAbilitySpecHandle Handle)
{
	if (this)
	{
		TArray<FGameplayAbilitySpec> Items = GetActivatableAbilities();
		for (int i = 0; i < Items.Num(); ++i)
		{
			FGameplayAbilitySpec Item = Items[i];
			if (Item.Handle == Handle)
			{
				return Item.GetAbilityInstances();
			}
		}
	}
	
	return TArray<UGameplayAbility*>();
}

UGameplayAbility* UGDAbilitySystemComponent::GetSingleAbilityInstance(FGameplayAbilitySpecHandle Handle)
{
	TArray<UGameplayAbility*> Abilites = GetAbilityInstances(Handle);
	if (Abilites.Num() > 0)
		return Abilites[0];

	return nullptr;
}

void UGDAbilitySystemComponent::K2_CancelAbility(TSubclassOf<UGameplayAbility> Ability)
{
	CancelAbility(Ability.GetDefaultObject());
}

bool UGDAbilitySystemComponent::HasAnyTagInOwner(TArray<FGameplayTag> Tags) const
{
	static FGameplayTagContainer AbilitySystemComponentTags;
	AbilitySystemComponentTags.Reset();
	GetOwnedGameplayTags(AbilitySystemComponentTags);
	
	for (int i = 0; i < Tags.Num(); ++i)
	{
		if (AbilitySystemComponentTags.HasTag(Tags[i]))
			return true;
	}

	return false;
}
