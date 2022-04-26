/* Copyright (C) 2019 Hugo ATTAL - All Rights Reserved
 * This plugin is downloadable from the UE4 Marketplace
 */

#pragma once

#include "CoreMinimal.h"
//#include "AnimationBlueprintEditor/Private/AnimGraphConnectionDrawingPolicy.cpp"
#include "ENConnectionDrawingPolicy.h"


class FSlateWindowElementList;
class UEdGraph;

class FENAnimGraphConnectionDrawingPolicy : public FKismetConnectionDrawingPolicy
{
public:

    // FKismetConnectionDrawingPolicy interface
    virtual bool TreatWireAsExecutionPin(UEdGraphPin* InputPin, UEdGraphPin* OutputPin) const override;
    virtual void BuildExecutionRoadmap() override;
    virtual void DetermineStyleOfExecWire(float& Thickness, FLinearColor& WireColor, bool& bDrawBubbles, const FTimePair& Times) override;
    // End of FKismetConnectionDrawingPolicy interface
    
    FENAnimGraphConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj)
    : FKismetConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, ZoomFactor, InClippingRect, InDrawElements, InGraphObj)
    {
        this->ConnectionDrawingPolicy = new FENConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, ZoomFactor, InClippingRect, InDrawElements, InGraphObj);
    }

    virtual void DrawConnection(int32 LayerId, const FVector2D& Start, const FVector2D& End, const FConnectionParams& Params) override;

    ~FENAnimGraphConnectionDrawingPolicy()
    {
        delete ConnectionDrawingPolicy;
    }

private:
    FENConnectionDrawingPolicy* ConnectionDrawingPolicy;
};