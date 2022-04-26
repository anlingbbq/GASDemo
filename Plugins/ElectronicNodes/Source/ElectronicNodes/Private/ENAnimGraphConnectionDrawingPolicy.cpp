/* Copyright (C) 2019 Hugo ATTAL - All Rights Reserved
* This plugin is downloadable from the UE4 Marketplace
*/

#include "ENAnimGraphConnectionDrawingPolicy.h"
#include "Animation/AnimBlueprint.h"
#include "Animation/AnimBlueprintGeneratedClass.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "AnimationGraphSchema.h"
#include "AnimGraphNode_Base.h"

void FENAnimGraphConnectionDrawingPolicy::DrawConnection(int32 LayerId, const FVector2D& Start, const FVector2D& End, const FConnectionParams& Params)
{
	this->ConnectionDrawingPolicy->SetMousePosition(LocalMousePosition);
	this->ConnectionDrawingPolicy->DrawConnection(LayerId, Start, End, Params);
	SplineOverlapResult = FGraphSplineOverlapResult(this->ConnectionDrawingPolicy->SplineOverlapResult);
}

bool FENAnimGraphConnectionDrawingPolicy::TreatWireAsExecutionPin(UEdGraphPin* InputPin, UEdGraphPin* OutputPin) const
{
	const UAnimationGraphSchema* Schema = GetDefault<UAnimationGraphSchema>();

	return (InputPin != NULL) && (Schema->IsPosePin(OutputPin->PinType));
}

void FENAnimGraphConnectionDrawingPolicy::BuildExecutionRoadmap()
{
	if(UAnimBlueprint* TargetBP = Cast<UAnimBlueprint>(FBlueprintEditorUtils::FindBlueprintForGraph(GraphObj)))
	{
	UAnimBlueprintGeneratedClass* AnimBlueprintClass = (UAnimBlueprintGeneratedClass*)(*(TargetBP->GeneratedClass));

	if (TargetBP->GetObjectBeingDebugged() == NULL)
	{
		return;
	}

	TMap<FProperty*, UObject*> PropertySourceMap;
	AnimBlueprintClass->GetDebugData().GenerateReversePropertyMap(/*out*/ PropertySourceMap);

	FAnimBlueprintDebugData& DebugInfo = AnimBlueprintClass->GetAnimBlueprintDebugData();
	for (auto VisitIt = DebugInfo.UpdatedNodesThisFrame.CreateIterator(); VisitIt; ++VisitIt)
	{
		const FAnimBlueprintDebugData::FNodeVisit& VisitRecord = *VisitIt;

		if ((VisitRecord.SourceID >= 0) && (VisitRecord.SourceID < AnimBlueprintClass->GetAnimNodeProperties().Num()) && (VisitRecord.TargetID >= 0) && (VisitRecord.TargetID < AnimBlueprintClass->AnimNodeProperties.Num()))
		{
			if (UAnimGraphNode_Base* SourceNode = Cast<UAnimGraphNode_Base>(PropertySourceMap.FindRef(AnimBlueprintClass->GetAnimNodeProperties()[VisitRecord.SourceID])))
			{
				if (UAnimGraphNode_Base* TargetNode = Cast<UAnimGraphNode_Base>(PropertySourceMap.FindRef(AnimBlueprintClass->GetAnimNodeProperties()[VisitRecord.TargetID])))
				{
					UEdGraphPin* PoseNet = NULL;

					UAnimationGraphSchema const* AnimSchema = GetDefault<UAnimationGraphSchema>();
					for (int32 PinIndex = 0; PinIndex < TargetNode->Pins.Num(); ++PinIndex)
					{
						UEdGraphPin* Pin = TargetNode->Pins[PinIndex];
						check(Pin);
						if (AnimSchema->IsPosePin(Pin->PinType) && (Pin->Direction == EGPD_Output))
						{
							PoseNet = Pin;
							break;
						}
					}

					if (PoseNet != NULL)
					{
						//@TODO: Extend the rendering code to allow using the recorded blend weight instead of faked exec times
						FExecPairingMap& Predecessors = PredecessorPins.FindOrAdd((UEdGraphNode*)SourceNode);
						FTimePair& Timings = Predecessors.FindOrAdd(PoseNet);
						Timings.PredExecTime = 0.0;
						Timings.ThisExecTime = FMath::Clamp(VisitRecord.Weight, 0.f, 1.f);
					}
				}
			}
		}
	}
	}
}

void FENAnimGraphConnectionDrawingPolicy::DetermineStyleOfExecWire(float& Thickness, FLinearColor& WireColor, bool& bDrawBubbles, const FTimePair& Times)
{
	// It's a followed link, make it strong and yellowish but fading over time
	const double BlendWeight = Times.ThisExecTime;

	const float HeavyBlendThickness = AttackWireThickness;
	const float LightBlendThickness = SustainWireThickness;

	Thickness = FMath::Lerp<float>(LightBlendThickness, HeavyBlendThickness, BlendWeight);
	WireColor = WireColor * (BlendWeight * 0.5f + 0.5f);//FMath::Lerp<FLinearColor>(SustainColor, AttackColor, BlendWeight);

	bDrawBubbles = true;
}

