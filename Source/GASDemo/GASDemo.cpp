// Copyright Epic Games, Inc. All Rights Reserved.

#include "GASDemo.h"
#include "Modules/ModuleManager.h"

class FGASDemoModuleImpl : public FDefaultGameModuleImpl
{
	bool IsGameModule() const override
	{
		return true;
	}

	void StartupModule() override
	{
		FDefaultGameModuleImpl::StartupModule();
		FCommandLine::Set(TEXT("-NetDriverOverrides=/Script/GASDemo.GDNetDriver"));
	}

	void ShutdownModule() override
	{
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE(FGASDemoModuleImpl, GASDemo, "GASDemo" );
 