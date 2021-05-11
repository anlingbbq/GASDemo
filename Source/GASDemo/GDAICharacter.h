// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "GameFramework/Character.h"
#include "GDAICharacter.generated.h"

UCLASS()
class GASDEMO_API AGDAICharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGDAICharacter();

	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(BlueprintImplementableEvent)
		void PlayerStateReady();

	UFUNCTION(BlueprintCallable, Category = "GAS|GDCharacter|Attributes")
		int32 GetCharacterLevel() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|GDCharacter|Attributes")
		float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|GDCharacter|Attributes")
		float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|GDCharacter|Attributes")
		float GetStamina() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|GDCharacter|Attributes")
		float GetMaxStamina() const;

	// Gets the Current value of MoveSpeed
	UFUNCTION(BlueprintCallable, Category = "GAS|GDCharacter|Attributes")
		float GetMoveSpeed() const;

	UFUNCTION(BlueprintPure)
		UGameplayAbility* GetAbilityInstanceByIndex(int32 Index);

	UFUNCTION(BlueprintImplementableEvent)
		void OnRunOutOfStamine();
	
protected:
	UPROPERTY()
		class UGDAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
		class UGDAttributeSetBase* AttributeSetBase;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Abilities")
		TArray<TSubclassOf<class UGDGameplayAbility>> CharacterAbilities;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Abilities")
		TSubclassOf<class UGameplayEffect> DefaultAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Abilities")
		TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	UFUNCTION(BlueprintImplementableEvent)
		void InitializeFloatBar(float CurValue, float MaxValue, UAbilitySystemComponent* ASC);

	void InitializeAttributes();
	void AddStartupEffects();
	void AddCharacterAbilities();

	TArray<FGameplayAbilitySpecHandle> AbilityHandles;
};
