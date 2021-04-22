// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GDCharacterBase.h"
#include "GDCharacter.generated.h"

/**
 *
 */
UCLASS()
class GASDEMO_API AGDCharacter : public AGDCharacterBase
{
	GENERATED_BODY()

public:
	AGDCharacter(const class FObjectInitializer& ObjectInitializer);

	virtual void PossessedBy(AController* NewController) override;

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

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Abilities")
		TArray<TSubclassOf<class UGDGameplayAbility>> CharacterAbilities;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Abilities")
		TSubclassOf<class UGameplayEffect> DefaultAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Abilities")
		TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	void InitializeAttributes();
	void AddStartupEffects();
	void AddCharacterAbilities();
};
