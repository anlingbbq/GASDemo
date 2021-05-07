// Fill out your copyright notice in the Description page of Project Settings.


#include "GDPlayerController.h"

#include "GDPlayerState.h"
#include "AbilitySystemComponent.h"

void AGDPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	UE_LOG(LogTemp, Warning, TEXT("Controller OnPossess %s"), GetLocalRole() == ROLE_Authority ? *FString("Server") : *FString("Client"))

	AGDPlayerState* PS = GetPlayerState<AGDPlayerState>();
	if (PS)
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	}
}

void AGDPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	UE_LOG(LogTemp, Warning, TEXT("Controller OnRep_PlayerState %s"), GetLocalRole() == ROLE_Authority ? *FString("Server") : *FString("Client"))
}
