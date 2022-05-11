// Fill out your copyright notice in the Description page of Project Settings.


#include "GDNetDriver.h"
#include "GameFramework/Character.h"
#include "Engine/NetworkObjectList.h"

UGDNetDriver::UGDNetDriver(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UGDNetDriver::ServerReplicateActors_CustomCondition(UNetConnection* InConnection,
	const TArray<FNetViewer>& InConnectionViewers, FActorPriority* InPriorityActors, double InElapsedTime)
{
	if (InPriorityActors->ActorInfo->Actor == nullptr)
	{
		return true;
	}
	ACharacter* Character = Cast<ACharacter>(InPriorityActors->ActorInfo->Actor);
	if (Character == nullptr || Character->GetNetConnection() == InConnection)
	{
		return true;
	}
	
	// 判断是否需要限制同步频率
	bool IsLimit = false;
	const FNetViewer* Viewer = &InConnectionViewers[0];
	if (Viewer)
	{
		FVector Dir = InPriorityActors->ActorInfo->Actor->GetActorLocation() - Viewer->ViewLocation;
		float DistSq = Dir.SizeSquared();
		// 目标在背后
		if ((Viewer->ViewDir | Dir) < 0.f)
		{
			IsLimit = true;
		}
		// 目标在前面 但有一定距离
		else if (DistSq > 1000000)
		{
			IsLimit = true;
		}
	}
	if (IsLimit)
	{
		double OldTime = LimitFrequencyMap.FindOrAdd(Character, InElapsedTime);
		if (InElapsedTime - OldTime > LimitFrequencyInterval)
		{
			LimitFrequencyMap[Character] = InElapsedTime;
			return true;
		}
		return false;
	}
	
	return true;
}
