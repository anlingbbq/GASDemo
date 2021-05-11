// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GDPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class GASDEMO_API AGDPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGDPlayerState();

	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	class UGDAttributeSetBase* GetAttributeSetBase() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|GDPlayerState|Attributes")
		float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|GDPlayerState|Attributes")
		float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|GDPlayerState|Attributes")
		float GetHealthRegenRate() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|GDPlayerState|Attributes")
		float GetStamina() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|GDPlayerState|Attributes")
		float GetMaxStamina() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|GDPlayerState|Attributes")
		float GetStaminaRegenRate() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|GDPlayerState|Attributes")
		float GetArmor() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|GDPlayerState|Attributes")
		float GetMoveSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|GDPlayerState|Attributes")
		float GetCharacterLevel() const;
	
protected:
	UPROPERTY()
		class UGDAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
		class UGDAttributeSetBase* AttributeSetBase;

	void BeginPlay() override;
};
