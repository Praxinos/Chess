#pragma once

#include "Piece.h"

#include "ChessRook.generated.h"

UCLASS()
class AChessRook : public APiece
{
    GENERATED_BODY()

public:
    AChessRook();

    virtual TArray<FMove> GetPiecePossibleMoves() override;
};
