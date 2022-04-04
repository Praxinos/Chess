#pragma once

#include "CoreMinimal.h"
#include "Move.h"

#include "Piece.generated.h"

class AInteractiveTile;

UCLASS(Abstract)
class APiece : public AActor
{
    GENERATED_BODY()

public:
    APiece();

public:
    void SetColor(bool iIsWhite);

    void Highlight();
    void RemoveHighlight();
    AInteractiveTile* GetTileOfPiece() const;
    virtual TArray<FMove> GetPiecePossibleMoves();

public:
    UPROPERTY()
    bool bIsWhite;

    UPROPERTY()
    UStaticMeshComponent* StaticMeshComponent;

    UPROPERTY()
    bool bFirstMove = true;
};
