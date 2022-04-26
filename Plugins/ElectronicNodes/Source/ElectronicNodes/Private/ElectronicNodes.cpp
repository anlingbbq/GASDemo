/* Copyright (C) 2019 Hugo ATTAL - All Rights Reserved
 * This plugin is downloadable from the UE4 Marketplace
 */

#include "ElectronicNodes.h"
#include "ENConnectionDrawingPolicy.h"
#include "ENCommands.h"
#include "MainFrame/Public/Interfaces/IMainFrameModule.h"

#define LOCTEXT_NAMESPACE "FElectronicNodesModule"

void FElectronicNodesModule::StartupModule()
{
    const TSharedPtr<FENConnectionDrawingPolicyFactory> ENConnectionFactory = MakeShareable(new FENConnectionDrawingPolicyFactory);
    FEdGraphUtilities::RegisterVisualPinConnectionFactory(ENConnectionFactory);

    auto const CommandBindings = FModuleManager::LoadModuleChecked< IMainFrameModule >("MainFrame").GetMainFrameCommandBindings();
    ENCommands::Register();
    
    CommandBindings->MapAction(
        ENCommands::Get().ToggleMasterActivation,
        FExecuteAction::CreateRaw(this, &FElectronicNodesModule::ToggleMasterActivation)
    );
}

void FElectronicNodesModule::ShutdownModule()
{
}

void FElectronicNodesModule::ToggleMasterActivation() const
{
    UElectronicNodesSettings& ElectronicNodesSettings = *GetMutableDefault<UElectronicNodesSettings>();
    ElectronicNodesSettings.ToggleMasterActivation();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FElectronicNodesModule, ElectronicNodes)
