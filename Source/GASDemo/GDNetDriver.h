// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystemUtils/Classes/IpNetDriver.h"
#include "GDNetDriver.generated.h"

/**
 *
 */
UCLASS()
class GASDEMO_API UGDNetDriver : public UIpNetDriver
{
	GENERATED_BODY()

public:
	UGDNetDriver(const class FObjectInitializer& ObjectInitializer);

	bool ServerReplicateActors_CustomCondition(UNetConnection* InConnection, const TArray<FNetViewer>& InConnectionViewers, FActorPriority* InPriorityActors, double InElapsedTime) override;

private:
	float LimitFrequencyInterval = 0.5f;
	TMap<ACharacter*, double> LimitFrequencyMap;
};
