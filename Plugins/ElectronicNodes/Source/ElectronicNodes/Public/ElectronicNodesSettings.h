/* Copyright (C) 2019 Hugo ATTAL - All Rights Reserved
 * This plugin is downloadable from the UE4 Marketplace
 */

#pragma once

#include "Engine/DeveloperSettings.h"
#include "ElectronicNodesSettings.generated.h"

UENUM(BlueprintType)
enum class EWireStyle : uint8
{
	Default,
	Manhattan,
	Subway
};

UENUM(BlueprintType)
enum class EWireAlignment : uint8
{
	Right,
	Left
};

UENUM(BlueprintType)
enum class EWirePriority : uint8
{
	None,
	Node,
	Pin
};

UENUM(BlueprintType)
enum class EBubbleDisplayRule : uint8
{
	Always,
	DisplayOnSelection,
	MoveOnSelection
};

UENUM(BlueprintType)
enum class ESelectionRule : uint8
{
	Near,
	Far
};

UCLASS(config = EditorPerProjectUserSettings, meta = (DisplayName = "Electronic Nodes Plugin"))
class ELECTRONICNODES_API UElectronicNodesSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UElectronicNodesSettings()
	{
		CategoryName = TEXT("Plugins");
		SectionName = TEXT("Electronic Nodes Plugin");
	}

	/* Activate or desactivate the whole plugin. Default: true */
	UPROPERTY(config, EditAnywhere, Category = "Activation")
	bool MasterActivate = true;

	/* Activate Electronic Nodes on Blueprint graphs. Default: true */
	UPROPERTY(config, EditAnywhere, Category = "Activation", meta = (EditCondition = "MasterActivate"))
	bool ActivateOnBlueprint = true;

	/* Activate Electronic Nodes on Material graphs. Default: true */
	UPROPERTY(config, EditAnywhere, Category = "Activation", meta = (EditCondition = "MasterActivate"))
	bool ActivateOnMaterial = true;

	/* Activate Electronic Nodes on Animation graphs. Default: true */
	UPROPERTY(config, EditAnywhere, Category = "Activation", meta = (EditCondition = "MasterActivate"))
	bool ActivateOnAnimation = true;

	/* Activate Electronic Nodes on VoxelPlugin (available on the marketplace). Default: true */
	UPROPERTY(config, EditAnywhere, Category = "Activation", meta = (EditCondition = "MasterActivate"))
	bool ActivateOnVoxelPlugin = true;

	/* Activate Electronic Nodes on VoxelPlugin (available on the marketplace). Default: true */
	UPROPERTY(config, EditAnywhere, Category = "Activation", meta = (EditCondition = "MasterActivate"))
	bool ActivateFallback = false;

	/* Wire style of graph. "Manhattan" is for 90deg angles, "Subway" is for 45deg angles. */
	UPROPERTY(config, EditAnywhere, Category = "Wire Style")
	EWireStyle WireStyle = EWireStyle::Subway;

	/* Specify wire alignment. Default: right. */
	UPROPERTY(config, EditAnywhere, Category = "Wire Style")
	EWireAlignment WireAlignment = EWireAlignment::Right;

	/* Specify wire alignment priority (when a Node is connected to a Pin). Default: none. */
	UPROPERTY(config, EditAnywhere, Category = "Wire Style")
	EWirePriority WirePriority = EWirePriority::None;

	/* Round radius of the wires. Default: 10 */
	UPROPERTY(config, EditAnywhere, Category = "Wire Style")
	uint32 RoundRadius = 10;

	/* Thickness of the wire (mutltiplier). Default: 1 */
	UPROPERTY(config, EditAnywhere, Category = "Wire Style", meta = (ClampMin = "0.0"))
	float WireThickness = 1.0f;

	/* Horizontal offset of wires from nodes. Default: 16 */
	UPROPERTY(config, EditAnywhere, Category = "Wire Style")
	uint32 HorizontalOffset = 16;

	/* Disable the offset for pins. Default: false */
	UPROPERTY(config, EditAnywhere, Category = "Wire Style")
	bool DisablePinOffset = false;

	/* Fix default zoomed-out wire displacement. Default: true */
	UPROPERTY(config, EditAnywhere, Category = "Wire Style")
	bool FixZoomDisplacement = true;

	/* Use a specific draw style for exec wires. Default: false */
	UPROPERTY(config, EditAnywhere, Category = "Exec Wire Style")
	bool OverwriteExecWireStyle = false;

	/* Specific wire style for exec wires. Default: Manhattan */
	UPROPERTY(config, EditAnywhere, Category = "Exec Wire Style", meta = (EditCondition = "OverwriteExecWireStyle"))
	EWireStyle WireStyleForExec = EWireStyle::Manhattan;

	/* Specify wire alignment for exe wires. Default: right. */
	UPROPERTY(config, EditAnywhere, Category = "Exec Wire Style", meta = (EditCondition = "OverwriteExecWireStyle"))
	EWireAlignment WireAlignmentForExec = EWireAlignment::Right;

	/* Specify wire alignment priority (when a Node is connected to a Pin) for exe wires. Default: node. */
	UPROPERTY(config, EditAnywhere, Category = "Exec Wire Style", meta = (EditCondition = "OverwriteExecWireStyle"))
	EWirePriority WirePriorityForExec = EWirePriority::Node;

	/* Activate ribbon cables for overlapping wires. */
	UPROPERTY(config, EditAnywhere, Category = "Ribbon Style (experimental)")
	bool ActivateRibbon = false;

	/* Offset between ribbon wires. Default: 4 */
	UPROPERTY(config, EditAnywhere, Category = "Ribbon Style (experimental)", meta = (EditCondition = "ActivateRibbon"))
	uint32 RibbonOffset = 4;

	/* Offset of wires when merge into ribbon. Default: 20 */
	UPROPERTY(config, EditAnywhere, Category = "Ribbon Style (experimental)", meta = (EditCondition = "ActivateRibbon"))
	uint32 RibbonMergeOffset = 20;

	/* Show moving bubbles on the wires. Default: false */
	UPROPERTY(config, EditAnywhere, Category = "Bubbles Style")
	bool ForceDrawBubbles = false;

	/* Display rules to show/move bubbles only near selected nodes. Default: Always */
	UPROPERTY(config, EditAnywhere, Category = "Bubbles Style", meta = (EditCondition = "ForceDrawBubbles"))
	EBubbleDisplayRule BubbleDisplayRule = EBubbleDisplayRule::Always;

	/* If selection only consider close nodes (near) or every related nodes (far). Default: Near */
	UPROPERTY(config, EditAnywhere, Category = "Bubbles Style", meta = (EditCondition = "ForceDrawBubbles"))
	ESelectionRule SelectionRule = ESelectionRule::Near;

	/* Disable bubbles above a certain zoom level. Default: -2 */
	UPROPERTY(config, EditAnywhere, Category = "Bubbles Style", meta = (EditCondition = "ForceDrawBubbles", ClampMin = "-12", ClampMax = "7"))
	int32 BubbleZoomThreshold = -2;

	/* Size of bubbles on the wires. Default: 2.0 */
	UPROPERTY(config, EditAnywhere, Category = "Bubbles Style", meta = (EditCondition = "ForceDrawBubbles", ClampMin = "1.0"))
	float BubbleSize = 2.0f;

	/* Speed of bubbles on the wires. Default: 4.0 */
	UPROPERTY(config, EditAnywhere, Category = "Bubbles Style", meta = (EditCondition = "ForceDrawBubbles", ClampMin = "0.0"))
	float BubbleSpeed = 4.0f;

	/* Space between bubbles on the wires. Default: 20.0 */
	UPROPERTY(config, EditAnywhere, Category = "Bubbles Style", meta = (EditCondition = "ForceDrawBubbles", ClampMin = "10.0"))
	float BubbleSpace = 20.0f;

	bool Debug = false;

	virtual FName GetContainerName() const override
	{
		return "Editor";
	}

	void ToggleMasterActivation()
	{
		MasterActivate = !MasterActivate;
	}
};
