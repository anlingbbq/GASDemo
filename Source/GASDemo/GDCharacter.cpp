// Fill out your copyright notice in the Description page of Project Settings.


#include "GDCharacter.h"
#include "GDAbilitySystemComponent.h"
#include "GDAttributeSetBase.h"
#include "GDGameplayAbility.h"
#include "GDPlayerController.h"
#include "GDPlayerState.h"

AGDCharacter::AGDCharacter(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

// Server Only
void AGDCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	UE_LOG(LogTemp, Warning, TEXT("Character PossessdBy %s"), GetLocalRole() == ROLE_Authority ? *FString("Server") : *FString("Client"))
	
	AGDPlayerState* PS = GetPlayerState<AGDPlayerState>();
	if (PS)
	{
		AbilitySystemComponent = Cast<UGDAbilitySystemComponent>(PS->GetAbilitySystemComponent());

		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

		AttributeSetBase = PS->GetAttributeSetBase();
		
		AGDPlayerController* PC = Cast<AGDPlayerController>(GetController());
		if (PC && PC->IsLocalPlayerController())
		{
			PC->CreateHUD();
		}

		if (!IsPlayerStateReady)
		{
			IsPlayerStateReady = true;
			PlayerStateReady();
		}
		
		// UI的属性修改事件的绑定和属性初始化的顺序有问题？ 临时处理
		FTimerHandle TempHandle;
		GetWorldTimerManager().SetTimer(TempHandle, [this]()
		{
			InitializeAttributes();
			AddStartupEffects();
			AddCharacterAbilities();

			if (!IsLocallyControlled())
			{
				InitializeFloatBar(GetHealth(), GetMaxHealth(), GetAbilitySystemComponent());
			}
		}, 0.5f, false);
	}
}

// Client Only
void AGDCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	UE_LOG(LogTemp, Warning, TEXT("Character OnRep_PlayerState %s"), GetLocalRole() == ROLE_Authority ? *FString("Server") : *FString("Client"))

	AGDPlayerState* PS = GetPlayerState<AGDPlayerState>();
	if (PS)
	{
		AbilitySystemComponent = Cast<UGDAbilitySystemComponent>(PS->GetAbilitySystemComponent());

		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

		AttributeSetBase = PS->GetAttributeSetBase();

		AGDPlayerController* PC = Cast<AGDPlayerController>(GetController());
		if (PC && PC->IsLocalPlayerController())
		{
			PC->CreateHUD();
		}

		if (!IsPlayerStateReady)
		{
			IsPlayerStateReady = true;
			PlayerStateReady();
		}
		
		// UI的属性修改事件的绑定和属性初始化的顺序有问题？ 临时处理
		FTimerHandle TempHandle;
		GetWorldTimerManager().SetTimer(TempHandle, [this]()
		{
			InitializeAttributes();
			AddStartupEffects();
			AddCharacterAbilities();
			AttributeSetBase->SetHealth(GetMaxHealth());
			AttributeSetBase->SetStamina(GetMaxStamina());

			if (!IsLocallyControlled())
			{
				InitializeFloatBar(GetHealth(), GetMaxHealth(), GetAbilitySystemComponent());
			}
		}, 0.5f, false);
	}
}

int32 AGDCharacter::GetCharacterLevel() const
{
	if (AttributeSetBase.IsValid())
	{
		return static_cast<int32>(AttributeSetBase->GetCharacterLevel());
	}

	return 0;
}

float AGDCharacter::GetHealth() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetHealth();
	}

	return 0.0f;
}

float AGDCharacter::GetMaxHealth() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMaxHealth();
	}

	return 0.0f;
}

float AGDCharacter::GetStamina() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetStamina();
	}

	return 0.0f;
}

float AGDCharacter::GetMaxStamina() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMaxStamina();
	}

	return 0.0f;
}

float AGDCharacter::GetMoveSpeed() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMoveSpeed();
	}

	return 0.0f;
}

UGameplayAbility* AGDCharacter::GetAbilityInstanceByIndex(int32 Index)
{
	if (Index < AbilityHandles.Num())
		return AbilitySystemComponent->GetSingleAbilityInstance(AbilityHandles[Index]);

	return nullptr;
}

void AGDCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGDCharacter::InitializeAttributes()
{
	if (!AbilitySystemComponent.IsValid())
	{
		return;
	}


	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, GetCharacterLevel(), EffectContext);
	if (NewHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	}
}

void AGDCharacter::AddStartupEffects()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid())
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, GetCharacterLevel(), EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
		}
	}
}

void AGDCharacter::AddCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid())
	{
		return;
	}

	for (TSubclassOf<UGDGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		AbilityHandles.Add(AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(StartupAbility, 1, INDEX_NONE, this)));
	}
}
