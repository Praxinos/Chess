#pragma once

#include "Piece.h"

#include "ChessBishop.generated.h"

UCLASS()
class AChessBishop : public APiece
{
    GENERATED_BODY()

public:
    AChessBishop();

    virtual TArray<FMove> GetPiecePossibleMoves() override;
};
