#pragma once

#include "CoreMinimal.h"
#include "InteractiveTile.generated.h"

class APiece;

UCLASS(MinimalAPI, Blueprintable)
class AInteractiveTile : public AActor
{
    GENERATED_BODY()
    AInteractiveTile();

public:
    void Highlight();
    void RemoveHighlight();
    APiece* GetPieceOnTile();

    UPROPERTY()
    UStaticMeshComponent* StaticMeshComponent;

    bool IsSelected;
};