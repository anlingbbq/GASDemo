// Copyright Epic Games, Inc. All Rights Reserved.

#include "GASDemoGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/GameUserSettings.h"

AGASDemoGameMode::AGASDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}

void AGASDemoGameMode::BeginPlay()
{
	if (GEngine)
	{
		UGameUserSettings* MyGameSettins = GEngine->GetGameUserSettings();
		MyGameSettins->SetScreenResolution(FIntPoint(640, 480));
		MyGameSettins->SetFullscreenMode(EWindowMode::Windowed);
		MyGameSettins->SetVSyncEnabled(false);
		MyGameSettins->ApplySettings(false);
	}
}
